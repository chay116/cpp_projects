/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_reader_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 00:30:26 by chalim            #+#    #+#             */
/*   Updated: 2021/07/23 22:55:53 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	find_end_object(t_data *data, t_sphere *new)
{
	t_sphere	*obj;

	new->next = 0;
	if (!(data->sphere))
		data->sphere = new;
	else
	{
		obj = data->sphere;
		while (obj->next)
			obj = obj->next;
		obj->next = new;
	}
}

void	set_sphere(char **words, t_data *data)
{
	char		*ptr1;
	t_sphere	*new;

	new = 0;
	ptr1 = words[2];
	if (!(new = (t_sphere *)malloc(sizeof(t_sphere))))
		ft_putstr_fd("Error\nError occurred during malloc of sphere.\n", 2);
	else if (words[1] == 0 || (put_pos(&(new->pos), words[1]) == ERR))
		ft_putstr_fd("Error\nInvalid input of position of sphere.\n", 2);
	else if (words[2] == 0 || !atoi_double(&ptr1, &(new->dia)) || \
	(new->dia <= 0) || *ptr1 != '\0')
		ft_putstr_fd("Error\nInvalid input of diameter of sphere.\n", 2);
	else if (words[3] == 0 || (put_color(&(new->color), words[3]) == ERR))
		ft_putstr_fd("Error\nInvalid input of color of sphere.\n", 2);
	else if (words[4] != 0)
		ft_putstr_fd("Error\nRedundant parameter in sphere setting.\n", 2);
	else
	{
		new->type = 1;
		find_end_object(data, new);
		return ;
	}
	exit(1);
}

void	set_plane(char **words, t_data *data)
{
	t_sphere	*new;

	new = 0;
	if (!(new = (t_sphere *)malloc(sizeof(t_sphere))))
		ft_putstr_fd("Error\nError occurred during malloc of plane.\n", 2);
	else if (words[1] == 0 || (put_pos(&(new->pos), words[1]) == ERR))
		ft_putstr_fd("Error\nInvalid input of position of plane.\n", 2);
	else if (words[2] == 0 || (put_vector(&(new->vec), words[2]) == ERR))
		ft_putstr_fd("Error\nInvalid input of ori vector of plane.\n", 2);
	else if (words[3] == 0 || (put_color(&(new->color), words[3]) == ERR))
		ft_putstr_fd("Error\nInvalid input of color of plane.\n", 2);
	else if (words[4] != 0)
		ft_putstr_fd("Error\nRedundant parameter in plane setting.\n", 2);
	else
	{
		new->type = 2;
		find_end_object(data, new);
		return ;
	}
	exit(1);
}

void	set_cylinder_sub(char **words, t_data *data, t_sphere *new)
{
	char		*ptr2;

	ptr2 = words[4];
	if (words[4] == 0 || !atoi_double(&ptr2, &(new->height)) || \
	(new->height <= 0) || *ptr2 != '\0')
		ft_putstr_fd("Error\nWrong input of height of cylinder.\n", 2);
	else if (words[5] == 0 || (put_color(&(new->color), words[5]) == ERR))
		ft_putstr_fd("Error\nInvalid input of color of cylinder.\n", 2);
	else if (words[6] != 0)
		ft_putstr_fd("Error\nRedundant parameter in cylinder setting.\n", 2);
	else
	{
		new->type = 3;
		find_end_object(data, new);
		return ;
	}
	exit(1);
}

void	set_cylinder(char **words, t_data *data)
{
	char		*ptr1;
	t_sphere	*new;

	new = 0;
	ptr1 = words[3];
	if (!(new = (t_sphere *)malloc(sizeof(t_sphere))))
		ft_putstr_fd("Error\nError occurred during malloc of cylinder.\n", 2);
	else if (words[1] == 0 || (put_pos(&(new->pos), words[1]) == ERR))
		ft_putstr_fd("Error\nInvalid input of position of cylinder.\n", 2);
	else if (words[2] == 0 || (put_vector(&(new->vec), words[2]) == ERR))
		ft_putstr_fd("Error\nInvalid input of ori vector of cylinder.\n", 2);
	else if (words[4] == 0 || !atoi_double(&ptr1, &(new->dia)) || \
	(new->dia <= 0) || *ptr1 != '\0')
		ft_putstr_fd("Error\nWrong input of diameter of cylinder.\n", 2);
	else
		set_cylinder_sub(words, data, new);
}
