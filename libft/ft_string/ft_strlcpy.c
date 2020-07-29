/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 18:40:56 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:24:05 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** The strlcpy() function copies up to num - 1 characters from the
** NUL-terminated string src to dest, NUL-terminating the result.
*/

size_t		ft_strlcpy(char *dest, const char *src, size_t num)
{
	char	*ptr;

	if ((ptr = ft_memccpy(dest, src, '\0', num)))
		return (ptr - dest - 1);
	dest[num - 1] = '\0';
	return (num + ft_strlen(src + num));
}
