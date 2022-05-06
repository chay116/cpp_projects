/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:54:34 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 10:23:47 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*ptr;

	ptr = (char *)s;
	len = ft_strlen(ptr) + 1;
	while (1)
	{
		if (ptr[--len] == (unsigned char)c)
			return (ptr + len);
		if (!len)
			break ;
	}
	return (0);
}
