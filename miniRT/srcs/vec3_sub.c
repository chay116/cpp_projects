/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 04:36:31 by chalim            #+#    #+#             */
/*   Updated: 2021/07/18 12:26:10 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	cal_vec_vec(t_vec3 *vec1, char operator, t_vec3 *vec2, t_vec3 *res)
{
	if (operator == '+')
	{
		res->x = vec1->x + vec2->x;
		res->y = vec1->y + vec2->y;
		res->z = vec1->z + vec2->z;
	}
	else if (operator == '-')
	{
		res->x = vec1->x - vec2->x;
		res->y = vec1->y - vec2->y;
		res->z = vec1->z - vec2->z;
	}
	else if (operator == '*')
	{
		res->x = vec1->x * vec2->x;
		res->y = vec1->y * vec2->y;
		res->z = vec1->z * vec2->z;
	}
	else if (operator == '/')
	{
		res->x = vec1->x / vec2->x;
		res->y = vec1->y / vec2->y;
		res->z = vec1->z / vec2->z;
	}
}

void	cal_vec_num(t_vec3 *vec1, char operator, double num, t_vec3 *res)
{
	if (operator == '+')
	{
		res->x = vec1->x + num;
		res->y = vec1->y + num;
		res->z = vec1->z + num;
	}
	else if (operator == '-')
	{
		res->x = vec1->x - num;
		res->y = vec1->y - num;
		res->z = vec1->z - num;
	}
	else if (operator == '*')
	{
		res->x = vec1->x * num;
		res->y = vec1->y * num;
		res->z = vec1->z * num;
	}
	else if (operator == '/')
	{
		res->x = vec1->x / num;
		res->y = vec1->y / num;
		res->z = vec1->z / num;
	}
}

void	set_ending(void)
{
	ft_putstr_fd("Error\nInvalid setting.\n", 2);
	exit(1);
}
