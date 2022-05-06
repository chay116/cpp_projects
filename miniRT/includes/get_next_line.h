/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:55:58 by chalim            #+#    #+#             */
/*   Updated: 2021/07/07 20:39:01 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  4
# endif
# define FD_MAX 256

typedef	struct	s_fdstore
{
	int				fd;
	int				pos;
	unsigned char	buff[BUFFER_SIZE + 1];
}				t_fdstore;

int				get_next_line(int fd, char **line);
int				read_line(t_fdstore *file, unsigned char **line, \
				unsigned char *buff);
int				check_buff(unsigned char *buff, int size);
int				gnl_makeup(t_fdstore *file, unsigned char **line);
unsigned char	*gnl_strjoin(unsigned char *s1, unsigned char *s2, int size);
void			store_buff(int check_pos, t_fdstore *file, \
				int sizeofbuff, unsigned char *buff);
int				gnl_strlen(unsigned char *str);

#endif
