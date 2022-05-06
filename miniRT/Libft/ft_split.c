/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 09:49:12 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 12:36:03 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char *s, char c)
{
	size_t	count;
	size_t	start_word;

	count = 0;
	start_word = 1;
	while (*s)
	{
		if (c != *s && start_word)
		{
			start_word = 0;
			count++;
		}
		else if (c == *s && !start_word)
			start_word = 1;
		s++;
	}
	return (count);
}

static int		make_array(char **result, char *s, char c, size_t word_total)
{
	char	*arr;
	size_t	len;

	while (word_total--)
	{
		while (*s && c == *s)
			s++;
		len = 0;
		while (*s && c != *s)
		{
			s++;
			len++;
		}
		arr = (char *)malloc((len + 1) * sizeof(char));
		if (!arr)
			return (0);
		*result = arr;
		while (len)
			*arr++ = *(s - len--);
		*arr = 0;
		result++;
	}
	return (1);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	size_t	word_total;
	size_t	pos;

	if (!s)
		return (0);
	word_total = count_word((char *)s, c);
	result = (char **)malloc((word_total + 1) * sizeof(char *));
	if (!result)
		return (0);
	pos = 0;
	while (pos < word_total + 1)
		result[pos++] = 0;
	if (!make_array(result, (char *)s, c, word_total))
	{
		pos = 0;
		while (result[pos])
			free(result[pos++]);
		free(result);
	}
	return (result);
}
