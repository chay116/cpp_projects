/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 21:13:52 by chalim            #+#    #+#             */
/*   Updated: 2021/07/18 12:26:06 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	inner_vec3(t_vec3 *vec1, t_vec3 *vec2)
{
	return ((vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z));
}

void	outer_vec3(t_vec3 *vec1, t_vec3 *vec2, t_vec3 *new_vec3)
{
	new_vec3->x = vec1->y * vec2->z - vec1->z * vec2->y;
	new_vec3->y = vec1->z * vec2->x - vec1->x * vec2->z;
	new_vec3->z = vec1->x * vec2->y - vec1->y * vec2->x;
}

double	size_vec3(t_vec3 *vec)
{
	return (sqrt(inner_vec3(vec, vec)));
}

void	norm_vec(t_vec3 *vec)
{
	double	size;

	size = size_vec3(vec);
	vec->x = vec->x / size;
	vec->y = vec->y / size;
	vec->z = vec->z / size;
}
