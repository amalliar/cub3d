/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 17:24:36 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:23:12 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Allocates (with malloc) and returns a new string, which is
** the result of the concatenation of 'str1' and 'str2'.
*/

char	*ft_strjoin(const char *str1, const char *str2)
{
	char		*big;
	size_t		len1;
	size_t		len2;

	if (!str1 || !str2)
		return (NULL);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (!(big = (char *)malloc(len1 + len2 + 1)))
		return (NULL);
	ft_memcpy(big, str1, len1);
	ft_memcpy(big + len1, str2, len2 + 1);
	return (big);
}
