/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:23:03 by chalim            #+#    #+#             */
/*   Updated: 2021/05/07 11:23:41 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t			i;
	unsigned char	*pptr1;
	unsigned char	*pptr2;

	pptr1 = (unsigned char *)ptr1;
	pptr2 = (unsigned char *)ptr2;
	i = 0;
	while (i < num && (*pptr1 == *pptr2))
	{
		pptr1++;
		pptr2++;
		i++;
	}
	if (i == num)
		return (0);
	return ((int)(*pptr1 - *pptr2));
}
