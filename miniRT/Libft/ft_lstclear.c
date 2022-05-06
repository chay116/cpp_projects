/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 04:09:31 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 10:13:02 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur_list;
	t_list	*prev_list;

	if (!*lst)
		return ;
	cur_list = *lst;
	while (cur_list->next)
	{
		prev_list = cur_list;
		cur_list = cur_list->next;
		del(prev_list->content);
		free(prev_list);
	}
	*lst = 0;
	del(cur_list->content);
	free(cur_list);
}
