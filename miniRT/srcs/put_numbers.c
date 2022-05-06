/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:09:28 by chalim            #+#    #+#             */
/*   Updated: 2021/07/25 06:11:45 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		atoi_double(char **str, double *num)
{
	int		num1;
	double	num2;

	*num = 1.0;
	num1 = 0.0;
	num2 = 0.0;
	if (**str == '-')
	{
		*num = -1;
		(*str)++;
	}
	if (!(**str >= '0' && **str <= '9'))
		return (0);
	while (**str >= '0' && **str <= '9')
		num1 = num1 * 10 + *((*str)++) - '0';
	if (**str == '.')
	{
		(*str)++;
		if (!(**str >= '0' && **str <= '9'))
			return (0);
		while (**str >= '0' && **str <= '9')
			num2 = (num2 * 10 + *((*str)++) - '0') / 10;
	}
	*num = (num1 + num2) * *num;
	return (1);
}

int		put_pos(t_vec3 *vec, char *line)
{
	if (!atoi_double(&line, &(vec->x)))
		return (ERROR);
	if (*(line++) != ',')
		return (ERROR);
	if (!atoi_double(&line, &(vec->y)))
		return (ERROR);
	if (*(line++) != ',')
		return (ERROR);
	if (!atoi_double(&line, &(vec->z)))
		return (ERROR);
	if (*line != '\0')
		return (ERROR);
	return (GOOD);
}

int		put_vector(t_vec3 *vec, char *line)
{
	if (!atoi_double(&line, &(vec->x)))
		return (ERROR);
	if (*(line++) != ',')
		return (ERROR);
	if (!atoi_double(&line, &(vec->y)))
		return (ERROR);
	if (*(line++) != ',')
		return (ERROR);
	if (!atoi_double(&line, &(vec->z)))
		return (ERROR);
	if (*line != '\0' || vec->x > 1.0 || vec->x < -1.0 \
	|| vec->y > 1.0 || vec->y < -1.0 || vec->z > 1.0 || vec->z < -1.0)
		return (ERROR);
	if (vec->x == 0 && vec->y == 0 & vec->z == 0)
		vec->x = 1;
	return (GOOD);
}

int		put_color(t_color *color, char *line)
{
	if (!atoi_double(&line, &(color->red)))
		return (ERROR);
	if (*(line++) != ',')
		return (ERROR);
	if (!atoi_double(&line, &(color->green)))
		return (ERROR);
	if (*(line++) != ',')
		return (ERROR);
	if (!atoi_double(&line, &(color->blue)))
		return (ERROR);
	if (*line != '\0' || color->red > 255.0 || color->red < 0.0 \
	|| color->blue > 255.0 || color->blue < 0.0 \
	|| color->green > 255.0 || color->green < 0.0)
		return (ERROR);
	return (GOOD);
}
