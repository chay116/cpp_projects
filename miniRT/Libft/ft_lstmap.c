/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 04:21:09 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 10:13:23 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*origin_list;
	t_list	*start_point;

	if (!lst)
		return (0);
	new_list = ft_lstnew((*f)(lst->content));
	if (!new_list)
		return (0);
	start_point = new_list;
	origin_list = lst->next;
	while (origin_list)
	{
		if (!(new_list->next = ft_lstnew((*f)(origin_list->content))))
		{
			ft_lstclear(&start_point, del);
			return (0);
		}
		origin_list = origin_list->next;
		new_list = new_list->next;
	}
	return (start_point);
}
