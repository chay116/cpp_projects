/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:06:52 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 12:32:49 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dest)
		return (0);
	while ((i + 1 < size) && *src)
	{
		*dest = *src;
		src++;
		dest++;
		i++;
	}
	while (*src)
	{
		src++;
		i++;
	}
	if (size)
		*dest = 0;
	return (i);
}
