/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tracing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 07:10:40 by chalim            #+#    #+#             */
/*   Updated: 2021/07/27 01:40:33 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	color_amb(t_data *data, t_color *diff)
{
	double	tmp;

	diff->red = 0;
	diff->blue = 0;
	diff->green = 0;
	tmp = (data->a_color.red > data->result.target->color.red) ? \
	data->result.target->color.red : data->a_color.red;
	diff->red += tmp * data->a_power;
	tmp = (data->a_color.blue > data->result.target->color.blue) ? \
	data->result.target->color.blue : data->a_color.blue;
	diff->blue += tmp * data->a_power;
	tmp = (data->a_color.green > data->result.target->color.green) ? \
	data->result.target->color.green : data->a_color.green;
	diff->green += tmp * data->a_power;
}

void	color_diff(t_data *data, t_color *diff, t_vec3 *light_vec)
{
	double		diff_power;
	double		tmp;

	diff_power = inner_vec3(light_vec, &(data->result.norm)) \
		/ size_vec3(&(data->result.norm)) / size_vec3(light_vec);
	if (diff_power > 0)
	{
		tmp = (data->light->color.red > data->result.target->color.red) ? \
		data->result.target->color.red : data->light->color.red;
		diff->red += tmp * data->light->power * diff_power;
		tmp = (data->light->color.blue > data->result.target->color.blue) ? \
		data->result.target->color.blue : data->light->color.blue;
		diff->blue += tmp * data->light->power * diff_power;
		tmp = (data->light->color.green > data->result.target->color.green) ? \
		data->result.target->color.green : data->light->color.green;
		diff->green += tmp * data->light->power * diff_power;
	}
}

void	phong(t_data *data, float answer)
{
	t_color		color;
	t_vec3		spot;
	t_vec3		light_vec;
	t_result	result;
	double		ans;

	color_amb(data, &color);
	cal_vec_num(&(data->ray), '*', answer, &spot);
	cal_vec_vec(&spot, '+', &(data->c_pos), &spot);
	cal_vec_vec(&(data->light->pos), '-', &spot, &light_vec);
	ans = find_closest(data, &light_vec, &spot, &result);
	cal_vec_vec(&spot, '-', &(data->light->pos), &spot);
	if (((ans < 0) || (ans > size_vec3(&spot) / size_vec3(&light_vec))) \
		&& (data->result.norm.in == false))
		color_diff(data, &color, &light_vec);
	insert_color(&color, data);
}

int		mlx_color(t_data *data)
{
	double	answer;

	answer = find_closest(data, &(data->ray), &(data->c_pos), &(data->result));
	if (answer < 0.0)
		data->addr[data->pos] = ((unsigned char)0 << 16 \
		| (unsigned char)0 << 8 | (unsigned char)0);
	else
		phong(data, answer);
	return (0);
}
