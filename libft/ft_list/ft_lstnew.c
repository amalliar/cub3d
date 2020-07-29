/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 21:27:12 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 08:56:19 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/*
** Allocates (with malloc) and returns a new element. The variable
** 'content' is initialized with the value of the parameter 'content'.
** The variable 'next' is initialized to NULL.
*/

t_list		*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (elem != NULL)
	{
		elem->content = content;
		elem->next = NULL;
	}
	return (elem);
}
