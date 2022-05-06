/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 07:10:38 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 12:32:10 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_str;
	unsigned int	pos;
	unsigned int	s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	pos = 0;
	if (len > s_len)
		new_str = (char *)malloc(sizeof(char) * (s_len + 1));
	else
		new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (0);
	while (pos < len && (start + pos < s_len))
	{
		new_str[pos] = s[start + pos];
		pos++;
	}
	new_str[pos] = 0;
	return (new_str);
}
