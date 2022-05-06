/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 19:49:21 by chalim            #+#    #+#             */
/*   Updated: 2021/07/25 07:36:09 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	start_win(t_data *data)
{
	data->mlx_win = mlx_new_window(data->mlx, data->res_x, data->res_y, WIN);
	data->img = mlx_new_image(data->mlx, data->res_x, data->res_y);
	data->addr = (int *)mlx_get_data_addr(data->img, \
	&(data->bits_per_pixel), &(data->line_length), &(data->endian));
	data->zoom = 1.0;
	data->left = 0;
	data->right = 0;
	data->up = 0;
	data->down = 0;
	data->theta_up = 0;
	data->theta_down = 0;
	data->psi_left = 0;
	data->psi_right = 0;
	get_theta_psi(data);
	get_rxry(data);
}

void	print_error(char *filename)
{
	ft_putstr_fd("Error\nInvalid filename\n", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
	exit(1);
	errno = 0;
}

int		read_rt(char *filename, t_data *data)
{
	char	*line;
	int		in;

	line = 0;
	if ((in = open(filename, O_RDONLY)) < 0)
	{
		print_error(filename);
		return (ERROR);
	}
	while (!(data->error) && get_next_line(in, &line) == 1)
	{
		if ((int)*line != EOF)
		{
			rt_reader(line, data);
			free(line);
		}
		else
		{
			free(line);
			break ;
		}
	}
	rt_reader(line, data);
	free(line);
	return (check(data));
}

int		main(int argc, char *argv[])
{
	t_data	data;

	data.error = false;
	data.light = 0;
	data.sphere = 0;
	data.camera = false;
	data.amb = false;
	data.is_light = 0;
	if (argc == 1)
		ft_putstr_fd("Error\nNo input\n", 2);
	else if (argc > 2)
		ft_putstr_fd("Error\nToo many inputs\n", 2);
	else if (ft_strnstr(argv[1], ".rt\0", ft_strlen(argv[1])) == 0)
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
	else if (read_rt(argv[1], &data) == GOOD)
	{
		data.mlx = mlx_init();
		start_win(&data);
		mlx_hook(data.mlx_win, KEYPRESS, 1L << 0, ft_key_press, (void *)&data);
		mlx_hook(data.mlx_win, KEYREL, 1L << 1, ft_key_release, (void *)&data);
		mlx_draw(&data);
		mlx_loop_hook(data.mlx, mlx_draw, &data);
		mlx_loop(data.mlx);
	}
	exit(0);
}
