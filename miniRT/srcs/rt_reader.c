/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 21:49:23 by chalim            #+#    #+#             */
/*   Updated: 2021/12/07 11:38:29 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	find_end_light(t_data *data, t_light *new)
{
	t_light	*light;

	new->next = 0;
	if (!(data->light))
		data->light = new;
	else
	{
		light = data->light;
		while (light->next)
			light = light->next;
		light->next = new;
	}
}

void	set_light(char **words, t_data *data)
{
	char	*ptr1;
	t_light	*new;

	ptr1 = words[2];
	if (!(new = (t_light *)malloc(sizeof(t_light))))
		ft_putstr_fd("Error\nError occurred during malloc of light.\n", 2);
	else if (words[1] == 0 || (put_pos(&(new->pos), words[1]) == ERR))
		ft_putstr_fd("Error\nInvalid input of position of light.\n", 2);
	else if (words[2] == 0 || !atoi_double(&ptr1, &(new->power)) || \
	(new->power < 0) || (new->power > 1.0) || *ptr1 != '\0')
		ft_putstr_fd("Error\nWrong input of power of light.\n", 2);
	else if (words[3] == 0 || (put_color(&(new->color), words[3]) == ERR))
		ft_putstr_fd("Error\nInvalid input of color of light.\n", 2);
	else if (words[4] != 0)
		ft_putstr_fd("Error\nRedundant parameter in light setting.\n", 2);
	else
	{
		find_end_light(data, new);
		data->is_light += 1;
		return ;
	}
	if (new)
		free(new);
	data->error = 1;
}

void	set_ambient(char **words, t_data *data)
{
	char	*ptr1;

	ptr1 = words[1];
	if (data->amb)
	{
		data->error = true;
		ft_putstr_fd("Error\nMore than two ambient settings.\n", 2);
		return ;
	}
	data->amb = true;
	if (words[1] == 0 || !atoi_double(&ptr1, &(data->a_power)) || \
	(data->a_power < 0) || (data->a_power > 1.0) || *ptr1 != '\0')
		ft_putstr_fd("Error\nWrong input of power of ambient.\n", 2);
	else if (words[2] == 0 || (put_color(&(data->a_color), words[2]) == ERR))
		ft_putstr_fd("Error\nInvalid input of color of ambient.\n", 2);
	else if (words[3] != 0)
		ft_putstr_fd("Error\nRedundant parameter in ambient setting.\n", 2);
	else
		return ;
	data->error = 1;
}

void	set_camera(char **words, t_data *data)
{
	char	*ptr1;

	ptr1 = words[3];
	if (data->camera)
	{
		data->error = true;
		ft_putstr_fd("Error\nMore than two camera settings.\n", 2);
		return ;
	}
	data->camera = true;
	if (words[1] == 0 || (put_pos(&(data->c_pos), words[1]) == ERROR))
		ft_putstr_fd("Error\nInvalid input of position of view point.\n", 2);
	else if (words[2] == 0 || (put_vector(&(data->c_vec), words[2]) == ERR))
		ft_putstr_fd("Error\nInvalid input of ori vector of camera.\n", 2);
	else if (words[3] == 0 || !atoi_double(&ptr1, &(data->c_fov)) || \
	(data->c_fov < 0) || (data->c_fov > 180) || *ptr1 != '\0')
	{
		ft_putstr_fd("Error\nWrong input of FOV of camera.\n", 2);
	}
	else if (words[4] != 0)
		ft_putstr_fd("Error\nRedundant parameter in camera setting.\n", 2);
	else
		return ;
	data->error = 1;
}

int		rt_reader(char *line, t_data *data)
{
	char	**words;
	int		i;

	if (!*line)
		return (GOOD);
	words = ft_split(line, ' ');
	if (ft_strncmp((const char*)words[0], "C\0", 2) == 0)
		set_camera(words, data);
	else if (ft_strncmp((const char*)words[0], "A\0", 2) == 0)
		set_ambient(words, data);
	else if (ft_strncmp((const char*)words[0], "L\0", 2) == 0)
		set_light(words, data);
	else if (ft_strncmp((const char*)words[0], "sp\0", 3) == 0)
		set_sphere(words, data);
	else if (ft_strncmp((const char*)words[0], "pl\0", 3) == 0)
		set_plane(words, data);
	else if (ft_strncmp((const char*)words[0], "cy\0", 3) == 0)
		set_cylinder(words, data);
	else if (!(words[0][0] == '\n' || words[0][0] == 0))
		set_ending();
	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
	return (GOOD);
}
