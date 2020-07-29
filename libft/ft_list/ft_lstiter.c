/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 21:34:28 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 08:54:43 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/*
** Iterates the list 'lst' and applies the function 'func'
** to the content of each element.
*/

void	ft_lstiter(t_list *lst, void (*func)(void *))
{
	while (lst != NULL)
	{
		func(lst->content);
		lst = lst->next;
	}
}
