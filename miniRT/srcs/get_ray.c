/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 08:06:47 by chalim            #+#    #+#             */
/*   Updated: 2021/07/27 01:40:11 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		mlx_draw(t_data *data)
{
	double	i;
	double	j;

	mlx_key_operation(data);
	i = -1.0;
	while (i++ < data->res_x)
	{
		j = -1.0;
		while (j++ < data->res_y)
		{
			data->ray.x = -data->rx.x * (i - data->res_x / 2) - \
				data->ry.x * (j - data->res_y / 2) + data->c_vec.x;
			data->ray.y = -data->rx.y * (i - data->res_x / 2) - \
				data->ry.y * (j - data->res_y / 2) + data->c_vec.y;
			data->ray.z = -data->rx.z * (i - data->res_x / 2) - \
				data->ry.z * (j - data->res_y / 2) + data->c_vec.z;
			data->pos = i + j * data->res_x;
			mlx_color(data);
		}
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

int		check(t_data *data)
{
	data->res_x = _XSIZE;
	data->res_y = _YSIZE;
	if (data->error)
		return (ERROR);
	else if (!(data->amb))
		ft_putstr_fd("Error\nNo ambient\n", 2);
	else if (!(data->camera))
		ft_putstr_fd("Error\nNo camera\n", 2);
	else if (data->is_light == 0)
		ft_putstr_fd("Error\nNo Light\n", 2);
	else if (data->is_light == 2)
		ft_putstr_fd("Error\nMore than two light settings.\n", 2);
	else
		return (GOOD);
	return (ERROR);
}

void	get_theta_psi(t_data *data)
{
	data->psi = 0;
	if (data->c_vec.x == 0 && data->c_vec.y == 0 && data->c_vec.z > 0)
		data->theta = PI / 2;
	else if (data->c_vec.x == 0 && data->c_vec.y == 0 && data->c_vec.z < 0)
		data->theta = 3 * PI / 2;
	else
	{
		data->theta = asin(data->c_vec.z / sqrt(data->c_vec.x * data->c_vec.x + \
		data->c_vec.y * data->c_vec.y + data->c_vec.z * data->c_vec.z));
		data->psi = asin(data->c_vec.y / sqrt(data->c_vec.x * \
					data->c_vec.x + data->c_vec.y * data->c_vec.y));
	}
	data->r_unit = sqrt(inner_vec3(&(data->c_vec), &(data->c_vec))) * \
		tan(data->c_fov / 360 * PI) / sqrt(data->res_x * data->res_x + \
		data->res_y * data->res_y);
	data->c_size = size_vec3(&(data->c_vec));
	if (data->c_vec.x < 0)
		data->psi = PI - data->psi;
}

void	get_rxry(t_data *data)
{
	data->rx.x = -1 * data->r_unit * sin(data->psi);
	data->rx.y = data->r_unit * cos(data->psi);
	data->rx.z = 0;
	data->ry.x = -data->r_unit * sin(data->theta) * cos(data->psi);
	data->ry.y = -data->r_unit * sin(data->theta) * sin(data->psi);
	data->ry.z = data->r_unit * cos(data->theta);
	data->c_vec.x = data->c_size * cos(data->theta) * cos(data->psi);
	data->c_vec.y = data->c_size * cos(data->theta) * sin(data->psi);
	data->c_vec.z = data->c_size * sin(data->theta);
}
