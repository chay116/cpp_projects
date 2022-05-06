/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:59:47 by chalim            #+#    #+#             */
/*   Updated: 2021/06/05 04:16:55 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (!dest && !src)
		return (0);
	ptr1 = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	if (ptr1 <= ptr2)
	{
		i = 0;
		while (i < num)
		{
			ptr1[i] = ptr2[i];
			i++;
		}
	}
	else
	{
		i = num;
		while (i-- > 0)
			ptr1[i] = ptr2[i];
	}
	return (dest);
}
