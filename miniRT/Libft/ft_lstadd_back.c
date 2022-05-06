/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 04:05:46 by chalim            #+#    #+#             */
/*   Updated: 2021/05/08 09:18:09 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current_lst;

	current_lst = *lst;
	if (!current_lst)
	{
		*lst = new;
	}
	else
	{
		while (current_lst->next)
			current_lst = current_lst->next;
		current_lst->next = new;
	}
}
