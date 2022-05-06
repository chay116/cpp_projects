/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 21:46:39 by chalim            #+#    #+#             */
/*   Updated: 2021/05/26 16:40:10 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	read_line(t_fdstore *file, unsigned char **line, unsigned char *buff)
{
	int	read_num;
	int	check_pos;

	if (!gnl_makeup(file, line))
		return (1);
	read_num = read(file->fd, buff, BUFFER_SIZE);
	if (read_num == -1)
		return (-1);
	while (read_num)
	{
		check_pos = check_buff(buff, read_num);
		*line = gnl_strjoin(*line, buff, check_pos);
		if (!*line)
			return (-1);
		if (check_pos != read_num || read_num != BUFFER_SIZE)
		{
			store_buff(check_pos, file, read_num - 1, buff);
			if (check_pos != read_num)
				return (1);
			else
				return (0);
		}
		read_num = read(file->fd, buff, BUFFER_SIZE);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	unsigned char		*buff;
	int					read_result;
	static t_fdstore	files[FD_MAX + 1];

	if (line == 0)
		return (-1);
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD_MAX)
	{
		*line = 0;
		return (-1);
	}
	buff = (unsigned char *)malloc(sizeof(unsigned char) * (BUFFER_SIZE + 1));
	buff[BUFFER_SIZE] = 0;
	files[fd].fd = fd;
	read_result = read_line(&(files[fd]), (unsigned char **)line, buff);
	free(buff);
	if (read_result == -1)
	{
		if (*line)
			free(*line);
		*line = 0;
		return (-1);
	}
	return (read_result);
}
