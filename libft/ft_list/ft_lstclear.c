/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 21:11:27 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 08:52:53 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/*
** Deletes and frees the given element and every successor of that
** element, using the function 'del' and free(). Finally, the pointer
** to the list must be set to NULL.
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		elem = *lst;
		*lst = (*lst)->next;
		del(elem->content);
		free(elem);
	}
}
