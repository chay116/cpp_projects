/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:00:00 by chalim            #+#    #+#             */
/*   Updated: 2021/05/07 11:15:02 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t num)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)src;
	i = 0;
	while (i < num && (*ptr != (unsigned char)c))
	{
		i++;
		ptr++;
	}
	if (i == num)
		return (0);
	return ((void *)ptr);
}
