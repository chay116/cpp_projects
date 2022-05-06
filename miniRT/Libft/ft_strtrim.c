/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 09:00:50 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 12:31:00 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	abovezero(size_t x, size_t y)
{
	if (x >= y)
		return (x - y);
	else
		return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	bool	checkbox[257];
	size_t	index;
	size_t	s1_len;
	char	*result;

	if (!s1 || !set)
		return (0);
	index = 0;
	while (index < 257)
		checkbox[index++] = false;
	index = 0;
	while (set[index])
		checkbox[(unsigned char)set[index++]] = true;
	s1_len = ft_strlen(s1);
	index = 0;
	while (index < s1_len && checkbox[(unsigned char)s1[index]])
		index++;
	while (s1_len > 0 && checkbox[(unsigned char)s1[s1_len - 1]])
		s1_len--;
	result = ft_substr(s1, index, abovezero(s1_len, index));
	return (result);
}
