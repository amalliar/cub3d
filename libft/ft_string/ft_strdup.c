/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 16:35:45 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:22:40 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** The strdup() function returns a pointer to a new string which is a
** duplicate of the string str.  Memory for the new string is obtained
** with malloc(), and can be freed with free().
*/

char	*ft_strdup(const char *str)
{
	size_t		block_size;
	void		*ptr;

	block_size = ft_strlen(str) + 1;
	if (!(ptr = malloc(block_size)))
		return (NULL);
	return (ft_memcpy(ptr, str, block_size));
}
