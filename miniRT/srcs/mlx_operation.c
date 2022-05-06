/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 08:14:58 by chalim            #+#    #+#             */
/*   Updated: 2021/07/10 04:32:43 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		ft_key_press(int keycode, t_data *data)
{
	if (keycode == LEFT)
		data->left = 1;
	else if (keycode == RIGHT)
		data->right = 1;
	else if (keycode == UP)
		data->up = 1;
	else if (keycode == DOWN)
		data->down = 1;
	else if (keycode == PSI_LEFT)
		data->psi_left = 1;
	else if (keycode == PSI_RIGHT)
		data->psi_right = 1;
	else if (keycode == THETA_UP)
		data->theta_up = 1;
	else if (keycode == THETA_DOWN)
		data->theta_down = 1;
	else if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	return (0);
}

int		ft_key_release(int keycode, t_data *data)
{
	if (keycode == LEFT)
		data->left = 0;
	else if (keycode == RIGHT)
		data->right = 0;
	else if (keycode == UP)
		data->up = 0;
	else if (keycode == DOWN)
		data->down = 0;
	else if (keycode == PSI_LEFT)
		data->psi_left = 0;
	else if (keycode == PSI_RIGHT)
		data->psi_right = 0;
	else if (keycode == THETA_UP)
		data->theta_up = 0;
	else if (keycode == THETA_DOWN)
		data->theta_down = 0;
	return (0);
}

int		mlx_key_operation_sub(t_data *data)
{
	if (data->left == 1)
	{
		data->c_pos.x += data->rx.x * 10000;
		data->c_pos.y += data->rx.y * 10000;
		data->c_pos.z += data->rx.z * 10000;
	}
	else if (data->right == 1)
	{
		data->c_pos.x -= data->rx.x * 10000;
		data->c_pos.y -= data->rx.y * 10000;
		data->c_pos.z -= data->rx.z * 10000;
	}
	else if (data->theta_up == 1)
		data->theta += PI / 30;
	else if (data->theta_down == 1)
		data->theta -= PI / 30;
	else if (data->psi_left == 1)
		data->psi += PI / 30;
	else if (data->psi_right == 1)
		data->psi -= PI / 30;
	else
		return (0);
	return (1);
}

int		mlx_key_operation(t_data *data)
{
	if (data->up == 1)
	{
		data->c_pos.x += data->c_vec.x * 100;
		data->c_pos.y += data->c_vec.y * 100;
		data->c_pos.z += data->c_vec.z * 100;
	}
	else if (data->down == 1)
	{
		data->c_pos.x -= data->c_vec.x * 100;
		data->c_pos.y -= data->c_vec.y * 100;
		data->c_pos.z -= data->c_vec.z * 100;
	}
	else if (mlx_key_operation_sub(data) == 0)
		return (0);
	get_rxry(data);
	return (0);
}
