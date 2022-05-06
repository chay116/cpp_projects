/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:55:27 by chalim            #+#    #+#             */
/*   Updated: 2021/07/27 01:40:03 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	onhit(t_vec3 *ray_pos, t_sphere *cy, \
				t_vec3 *ray, double *an)
{
	t_vec3	a0;

	cal_vec_num(ray, '*', *an, &a0);
	cal_vec_vec(&a0, '+', ray_pos, &a0);
	cal_vec_vec(&a0, '-', &(cy->pos), &a0);
	cal_vec_num(&(cy->vec), '*', inner_vec3(&(cy->vec), &a0) \
		/ inner_vec3(&(cy->vec), &(cy->vec)), &a0);
	*(an + 2) = inner_vec3(&(cy->vec), &a0) / size_vec3(&(cy->vec));
	if (*(an + 2) < 0)
	{
		*(an + 4) = -1;
		*an = -1;
	}
	else if (*(an + 2) >= cy->height)
	{
		*(an + 4) = 1;
		*an = -1;
	}
	else
		*(an + 4) = 0;
}

int		get_answer(t_vec3 *ray_pos, t_sphere *cy, \
				t_vec3 *ray, double *an)
{
	t_vec3	a1;
	t_vec3	p1;
	t_vec3	c1;

	cal_vec_num(&(cy->vec), '*', inner_vec3(ray, &(cy->vec)) \
	/ inner_vec3(&(cy->vec), &(cy->vec)), &a1);
	cal_vec_vec(ray, '-', &a1, &a1);
	cal_vec_vec(ray_pos, '-', &(cy->pos), &p1);
	cal_vec_num(&(cy->vec), '*', inner_vec3(&p1, &(cy->vec)) \
	/ inner_vec3(&(cy->vec), &(cy->vec)), &c1);
	cal_vec_vec(&p1, '-', &c1, &c1);
	an[2] = (inner_vec3(&a1, &c1) * inner_vec3(&a1, &c1) \
	- inner_vec3(&a1, &a1) * (inner_vec3(&c1, &c1) - cy->dia * cy->dia));
	if (an[2] < 0)
		return (-1);
	an[0] = (-inner_vec3(&a1, &c1) - sqrt(an[2])) / inner_vec3(&a1, &a1);
	an[1] = (-inner_vec3(&a1, &c1) + sqrt(an[2])) / inner_vec3(&a1, &a1);
	if ((an[0] < 0) && (an[1] < 0))
		return (-1);
	onhit(ray_pos, cy, ray, an);
	onhit(ray_pos, cy, ray, an + 1);
	return (0);
}

double	hit_cylinder(t_vec3 *ray_pos, t_sphere *cy, t_vec3 *norm, t_vec3 *ray)
{
	t_sum	s;

	s.ray_pos = ray_pos;
	s.ray = ray;
	s.norm = norm;
	s.cy = cy;
	s.answer = -1;
	s.number = 0;
	if (get_answer(s.ray_pos, s.cy, s.ray, s.an) == -1)
		return (-1.0);
	if ((s.an)[4] * (s.an)[5] == 1)
		return (-1.0);
	cal_vec_num(norm, '*', 0, norm);
	s.norm->in = false;
	return (hit_cy(&s));
}

double	hit_downcircle(t_sum *s)
{
	t_vec3	oc;
	t_vec3	a1;
	double	det;
	double	answer;

	(s->an)[2] = 0;
	s->norm->x = -s->cy->vec.x;
	s->norm->y = -s->cy->vec.y;
	s->norm->z = -s->cy->vec.z;
	cal_vec_vec(&(s->cy->pos), '-', s->ray_pos, &oc);
	det = inner_vec3(&oc, &(s->cy->vec));
	answer = det / inner_vec3(s->ray, &(s->cy->vec));
	cal_vec_num(s->ray, '*', answer, &a1);
	cal_vec_vec(&oc, '-', &a1, &oc);
	if (size_vec3(&oc) > s->cy->dia)
		return (-1);
	if (answer > 0)
		(s->an)[2] = 1;
	return (answer);
}

double	hit_upcircle(t_sum *s)
{
	t_vec3	a1;
	t_vec3	oc;
	double	det;
	double	answer;

	(s->an)[3] = 0;
	s->norm->x = s->cy->vec.x;
	s->norm->y = s->cy->vec.y;
	s->norm->z = s->cy->vec.z;
	cal_vec_num(&(s->cy->vec), '*', s->cy->height / \
		size_vec3(&(s->cy->vec)), &a1);
	cal_vec_vec(&(s->cy->pos), '+', &a1, &a1);
	cal_vec_vec(&a1, '-', s->ray_pos, &oc);
	det = inner_vec3(&oc, &(s->cy->vec));
	answer = det / inner_vec3(s->ray, &(s->cy->vec));
	cal_vec_num(s->ray, '*', answer, &a1);
	cal_vec_vec(&oc, '-', &a1, &oc);
	if (size_vec3(&oc) > s->cy->dia)
		return (-1);
	if (answer > 0)
		(s->an)[3] = 1;
	return (answer);
}
