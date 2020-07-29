/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 21:40:08 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 08:55:45 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/*
** Iterates the list 'lst' and applies the function 'func' to the
** content of each element. Creates a new list resulting of the
** successive applications of the function 'func'. The 'del'
** function is used to delete the content of an element if needed.
*/

t_list		*process_content(void *content, void *(*func)(void *), \
				void (*del)(void *))
{
	t_list	*elem;
	void	*tmp;

	if (!(tmp = func(content)))
		return (NULL);
	if (!(elem = ft_lstnew(tmp)))
	{
		del(tmp);
		return (NULL);
	}
	return (elem);
}

t_list		*ft_lstmap(t_list *lst, void *(*func)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*tail;
	t_list	*elem;

	map = NULL;
	if (lst != NULL)
	{
		if (!(elem = process_content(lst->content, func, del)))
			return (NULL);
		ft_lstadd_back(&map, elem);
		tail = map;
		lst = lst->next;
	}
	while (lst != NULL)
	{
		if (!(elem = process_content(lst->content, func, del)))
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		ft_lstadd_back(&tail, elem);
		tail = tail->next;
		lst = lst->next;
	}
	return (map);
}
