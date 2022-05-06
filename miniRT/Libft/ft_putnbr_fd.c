/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:25:51 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 11:34:01 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print(int n, int fd)
{
	char	a;

	a = '0' + n % 10;
	if (n >= 10)
	{
		n = n / 10;
		ft_print(n, fd);
	}
	write(fd, &a, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n >= 0)
	{
		ft_print(n, fd);
	}
	else
	{
		write(fd, "-", 1);
		if (n == -2147483648)
		{
			write(fd, "2", 1);
			n = -147483648;
		}
		n *= -1;
		ft_print(n, fd);
	}
}
