/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 06:25:07 by chalim            #+#    #+#             */
/*   Updated: 2021/07/27 01:40:02 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	hit_plane(t_vec3 *ray_pos, t_sphere *sphere, t_vec3 *norm, t_vec3 *ray)
{
	t_vec3	oc;
	double	det;
	double	answer;

	norm->in = false;
	norm->x = sphere->vec.x;
	norm->y = sphere->vec.y;
	norm->z = sphere->vec.z;
	cal_vec_vec(&(sphere->pos), '-', ray_pos, &oc);
	det = inner_vec3(&oc, &(sphere->vec));
	answer = det / inner_vec3(ray, &(sphere->vec));
	if (det > 0)
		cal_vec_num(norm, '*', -1, norm);
	return (answer);
}

double	hit_sphere(t_vec3 *ray_pos, t_sphere *sphere, t_vec3 *norm, t_vec3 *ray)
{
	t_vec3	oc;
	double	det;
	double	answer;

	norm->in = false;
	cal_vec_vec(ray_pos, '-', &(sphere->pos), &oc);
	det = (inner_vec3(&oc, ray) * inner_vec3(&oc, ray) - inner_vec3(ray, ray) \
	* (inner_vec3(&oc, &oc) - sphere->dia * sphere->dia));
	if ((det <= 0))
		return (-1.0);
	answer = (-inner_vec3(&oc, ray) - sqrt(det)) / inner_vec3(ray, ray);
	cal_vec_num(ray, '*', answer, norm);
	cal_vec_vec(norm, '+', ray_pos, norm);
	cal_vec_vec(norm, '-', &(sphere->pos), norm);
	if (answer < 0)
	{
		answer = (-inner_vec3(&oc, ray) + sqrt(det)) / inner_vec3(ray, ray);
		cal_vec_num(ray, '*', -answer, norm);
		cal_vec_vec(norm, '-', ray_pos, norm);
		cal_vec_vec(norm, '+', &(sphere->pos), norm);
		norm->in = true;
	}
	return (answer);
}

double	hit_where(t_vec3 *ray_pos, t_sphere *sphere, t_vec3 *norm, t_vec3 *ray)
{
	if (sphere->type == 1)
		return (hit_sphere(ray_pos, sphere, norm, ray));
	else if (sphere->type == 2)
		return (hit_plane(ray_pos, sphere, norm, ray));
	else if (sphere->type == 3)
	{
		return (hit_cylinder(ray_pos, sphere, norm, ray));
	}
	return (-1);
}

double	find_closest(t_data *data, t_vec3 *ray, t_vec3 *pos, t_result *result)
{
	t_sphere	*sphere;
	double		answer;
	double		cls;
	t_vec3		norm;

	sphere = data->sphere;
	result->target = 0;
	norm.in = false;
	cls = -1;
	while (sphere)
	{
		if ((data->result.target != sphere) && \
		(answer = hit_where(pos, sphere, &(norm), ray)) > 0.0)
		{
			if (answer < cls || cls < 0)
			{
				result->target = sphere;
				cal_vec_num(&norm, '+', 0, &(result->norm));
				result->norm.in = norm.in;
				cls = answer;
			}
		}
		sphere = sphere->next;
	}
	return (cls);
}
