/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 20:01:01 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 18:43:03 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"

/*
** Reallocates the given area of memory. It must be previously allocated by
** malloc(), calloc() or realloc() and not yet freed with a call to free or
** realloc.
*/

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	new = malloc(new_size);
	if (new != NULL)
		ft_memcpy(new, ptr, (old_size < new_size) ? old_size : new_size);
	if (old_size != 0)
		free(ptr);
	return (new);
}
