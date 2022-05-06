/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:38:54 by chalim            #+#    #+#             */
/*   Updated: 2021/05/23 12:51:08 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void			store_buff(int check_pos, t_fdstore *file, int sizeofbuff \
		, unsigned char *buff)
{
	int	i;

	i = -1;
	file->pos = sizeofbuff - check_pos;
	if (file->pos == 0)
	{
		while (file->buff[++i] != 0)
			file->buff[i] = 0;
		return ;
	}
	while (++i < file->pos)
		file->buff[i] = buff[check_pos + 1 + i];
	while (file->buff[i] != 0)
		file->buff[i++] = 0;
}

int				check_buff(unsigned char *buff, int size)
{
	int	pos;

	pos = 0;
	while (pos < size && buff[pos] != '\n')
		pos++;
	return (pos);
}

int				gnl_makeup(t_fdstore *file, unsigned char **line)
{
	unsigned char	*dupstr1;
	int				i;
	int				j;

	j = -1;
	i = check_buff(file->buff, file->pos);
	dupstr1 = (unsigned char *)malloc((i + 1) * sizeof(unsigned char));
	if (!dupstr1)
		return (0);
	while (++j < i)
		dupstr1[j] = file->buff[j];
	dupstr1[j] = 0;
	*line = dupstr1;
	if (file->buff[i] == '\n')
	{
		file->buff[i] = 0;
		store_buff(i, file, file->pos - 1, file->buff);
		return (0);
	}
	else
	{
		store_buff(i - 1, file, file->pos - 1, file->buff);
		return (1);
	}
}

unsigned char	*gnl_strjoin(unsigned char *s1, unsigned char *s2, int size)
{
	unsigned char	*result;
	int				total;
	int				i;
	int				size_s1;

	size_s1 = gnl_strlen(s1);
	result = (unsigned char *)malloc((size_s1 + size + 1) \
			* sizeof(unsigned char));
	if (!result)
	{
		free(s1);
		return (0);
	}
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	total = i;
	i = -1;
	while (size > ++i)
		result[total + i] = s2[i];
	result[total + i] = 0;
	free(s1);
	return (result);
}

int				gnl_strlen(unsigned char *str)
{
	int	j;

	if (!str)
		return (0);
	j = 0;
	while (*str)
	{
		j++;
		str++;
	}
	return (j);
}
