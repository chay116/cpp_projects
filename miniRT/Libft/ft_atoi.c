/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:09:28 by chalim            #+#    #+#             */
/*   Updated: 2021/05/23 12:41:52 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(char *str)
{
	if ((*str == '\t') || (*str == '\n') || (*str == '\v'))
		return (1);
	else if ((*str == '\f') || (*str == '\r') || (*str == ' '))
		return (1);
	else
		return (0);
}

static int	is_sign(char *str, int *sign)
{
	if (*str == '+')
		return (1);
	else if (*str == '-')
	{
		*sign *= -1;
		return (1);
	}
	else
		return (0);
}

static int	is_number(char *str, int *num)
{
	if (*str >= '0' && *str <= '9')
	{
		*num = *num * 10 + *str - '0';
		return (1);
	}
	else
		return (0);
}

int			ft_atoi(char *str)
{
	int		num;
	int		sign;
	char	*ptr;

	ptr = (char *)str;
	sign = 1;
	num = 0;
	while (is_space(ptr))
		ptr++;
	if (is_sign(ptr, &sign))
		ptr++;
	while (is_number(ptr, &num))
		ptr++;
	return (num * sign);
}
