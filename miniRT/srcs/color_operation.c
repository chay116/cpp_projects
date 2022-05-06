/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 07:12:43 by chalim            #+#    #+#             */
/*   Updated: 2021/07/18 16:48:07 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	cal_col_col(t_color *vec1, char operator, t_color *vec2, t_color *res)
{
	if (operator == '+')
	{
		res->red = vec1->red + vec2->red;
		res->green = vec1->green + vec2->green;
		res->blue = vec1->blue + vec2->blue;
	}
	else if (operator == '-')
	{
		res->red = vec1->red - vec2->red;
		res->green = vec1->green - vec2->green;
		res->blue = vec1->blue - vec2->blue;
	}
	else if (operator == '*')
	{
		res->red = (int)(vec1->red * vec2->red);
		res->green = (int)(vec1->green * vec2->green);
		res->blue = (int)(vec1->blue * vec2->blue);
	}
	else if (operator == '/')
	{
		res->red = (int)(vec1->red / vec2->red);
		res->green = (int)(vec1->green / vec2->green);
		res->blue = (int)(vec1->blue / vec2->blue);
	}
}

void	cal_col_num(t_color *vec1, char operator, double num, t_color *res)
{
	if (operator == '+')
	{
		res->red = vec1->red + num;
		res->green = vec1->green + num;
		res->blue = vec1->blue + num;
	}
	else if (operator == '-')
	{
		res->red = vec1->red - num;
		res->green = vec1->green - num;
		res->blue = vec1->blue - num;
	}
	else if (operator == '*')
	{
		res->red = (int)(vec1->red * num);
		res->green = (int)(vec1->green * num);
		res->blue = (int)(vec1->blue * num);
	}
	else if (operator == '/')
	{
		res->red = (int)(vec1->red / num);
		res->green = (int)(vec1->green / num);
		res->blue = (int)(vec1->blue / num);
	}
}

void	insert_color(t_color *color, t_data *data)
{
	if (color->red > 255)
		color->red = 255;
	if (color->red < 0)
		color->red = 0;
	if (color->blue > 255)
		color->blue = 255;
	if (color->blue < 0)
		color->blue = 0;
	if (color->green > 255)
		color->green = 255;
	if (color->green < 0)
		color->green = 0;
	data->addr[data->pos] = ((unsigned char)color->red << 16 \
	| (unsigned char)color->green << 8 \
	| (unsigned char)color->blue);
}
