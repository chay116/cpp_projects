/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:08:42 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 11:34:45 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcmp1(char *s1, char *s2, size_t i, size_t len)
{
	while ((*s1 == *s2) && *s2)
	{
		s1++;
		s2++;
		i++;
	}
	if (!*s2 && i <= len)
		return (1);
	else
		return (0);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*str;
	char	*to_find;

	str = (char *)haystack;
	to_find = (char *)needle;
	i = 0;
	if (!*to_find)
		return (str);
	while (*str && i < len)
	{
		if (ft_strcmp1(str, to_find, i, len) == 1)
			return (str);
		str++;
		i++;
	}
	return (0);
}
