/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:58:40 by chalim            #+#    #+#             */
/*   Updated: 2021/05/07 11:05:11 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *ptr, size_t size)
{
	unsigned char	*arr;

	arr = ptr;
	while (size--)
	{
		*arr = 0;
		arr++;
	}
	return (ptr);
}
