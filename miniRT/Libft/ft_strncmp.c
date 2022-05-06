/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:33:55 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 10:33:16 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strncmp(const char *str1, const char *str2, unsigned int n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while ((*s1 == *s2) && (*s2) && (n > 0))
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	if (*s1 > *s2)
		return (1);
	else if (*s1 < *s2)
		return (-1);
	else
		return (0);
}
