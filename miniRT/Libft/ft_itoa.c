/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:34:11 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 12:33:48 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n)
{
	int	len;

	len = 1;
	if (n >= 0)
		n = n / 10;
	else
	{
		n = n / -10;
		len += 1;
	}
	while (n)
	{
		len += 1;
		n = n / 10;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int		len;
	char	*arr;

	len = num_len(n);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (0);
	arr[len] = 0;
	if (n <= 0)
	{
		arr[0] = '-';
		arr[--len] = '0' - n % -10;
		n = n / -10;
	}
	while (n)
	{
		arr[--len] = '0' + n % 10;
		n = n / 10;
	}
	return (arr);
}
