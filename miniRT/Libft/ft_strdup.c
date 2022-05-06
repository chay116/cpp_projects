/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:09:01 by chalim            #+#    #+#             */
/*   Updated: 2021/05/07 15:17:10 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char		*dupstr;
	size_t		len;

	len = ft_strlen(src);
	dupstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!dupstr)
		return (0);
	dupstr[len] = 0;
	while (len--)
	{
		dupstr[len] = src[len];
	}
	return (dupstr);
}
