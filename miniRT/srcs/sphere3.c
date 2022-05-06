/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 14:12:10 by chalim            #+#    #+#             */
/*   Updated: 2021/07/27 01:40:04 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	compare_cy(double a, double b)
{
	if (a <= 0 && b <= 0)
		return (-1);
	else if (a <= 0 && b > 0)
		return (b);
	else if (a > 0 && b <= 0)
		return (a);
	else if (a > 0 && b > 0)
	{
		if (a > b)
			return (b);
		else
			return (a);
	}
	return (-1);
}

double	get_norm(t_sum *s, double answer)
{
	t_vec3	a1;
	t_vec3	oc;
	double	det;

	cal_vec_num(s->ray, '*', answer, &a1);
	cal_vec_vec(&a1, '+', s->ray_pos, &a1);
	cal_vec_vec(&a1, '-', &(s->cy->pos), &a1);
	det = inner_vec3(&a1, &(s->cy->vec)) \
	/ inner_vec3(&(s->cy->vec), &(s->cy->vec));
	cal_vec_num(&(s->cy->vec), '*', det, &oc);
	cal_vec_vec(&a1, '-', &oc, s->norm);
	return (answer);
}

int		is_inside(t_sum *s)
{
	t_vec3	a1;
	t_vec3	oc;
	double	det;
	double	height;

	cal_vec_vec(s->ray_pos, '-', &(s->cy->pos), &oc);
	height = inner_vec3(&oc, &(s->cy->vec)) / size_vec3(&(s->cy->vec));
	cal_vec_num(&(s->cy->vec), '*', height / size_vec3(&(s->cy->vec)), &a1);
	cal_vec_vec(&(s->cy->pos), '+', &a1, &a1);
	cal_vec_vec(&a1, '-', s->ray_pos, &oc);
	det = inner_vec3(&oc, &(s->cy->vec));
	det = det / inner_vec3(s->ray, &(s->cy->vec));
	cal_vec_num(s->ray, '*', det, &a1);
	cal_vec_vec(&oc, '-', &a1, &oc);
	if ((height >= 0 && height < s->cy->height) \
		&& (size_vec3(&oc) < s->cy->dia))
		return (1);
	else
		return (0);
}

double	hit_cy(t_sum *s)
{
	double	down;
	double	up;
	double	answer;

	down = hit_downcircle(s);
	up = hit_upcircle(s);
	answer = compare_cy(down, up);
	answer = compare_cy(answer, (s->an)[0]);
	answer = compare_cy(answer, (s->an)[1]);
	if (is_inside(s))
		s->norm->in = true;
	if (answer == up)
		return (hit_upcircle(s));
	if (answer == down)
		return (hit_downcircle(s));
	if (answer == (s->an)[0])
		return (get_norm(s, (s->an)[0]));
	if (answer == (s->an)[1])
		return (get_norm(s, (s->an)[1]));
	return (-1.0);
}
