/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 18:08:17 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:26:55 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Allocates (with malloc) and returns a copy of 'str' with the
** characters specified in 'set' removed from the beginning and
** the end of the string.
*/

char	*ft_strtrim(const char *str, const char *set)
{
	char		*little;
	size_t		len;

	if (!str || !set)
		return (NULL);
	while (*str && ft_strchr(set, *str) != NULL)
		++str;
	len = ft_strlen(str);
	while (len && ft_strchr(set, str[len - 1]) != NULL)
		--len;
	if (!(little = (char *)malloc(len + 1)))
		return (NULL);
	ft_memcpy(little, str, len);
	little[len] = '\0';
	return (little);
}
