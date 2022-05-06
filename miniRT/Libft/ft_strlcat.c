/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:07:44 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 11:32:18 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len;
	size_t	destlen;
	size_t	i;

	destlen = ft_strlen(dest);
	len = 0;
	i = 0;
	while (i < destlen)
	{
		if (size > i)
			len++;
		i++;
	}
	while (*src)
	{
		if (size > i + 1)
			dest[i++] = *src;
		src++;
		len++;
	}
	if (destlen < size)
		*(dest + i) = 0;
	return (len);
}
