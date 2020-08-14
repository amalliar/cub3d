/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 20:58:08 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/13 15:13:37 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/*
** Adds the element 'new' at the end of the list.
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	static t_list	*old_lst;
	static t_list	*elem;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		old_lst = new;
		elem = new;
		return ;
	}
	if (*lst == old_lst)
	{
		elem->next = new;
		elem = elem->next;
		return ;
	}
	old_lst = *lst;
	elem = *lst;
	while (elem->next != NULL)
		elem = elem->next;
	elem->next = new;
	elem = elem->next;
}
