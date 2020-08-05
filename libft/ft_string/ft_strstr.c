/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 21:04:34 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/05 21:17:27 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** The ft_strstr() function locates the first occurrence of the
** null-terminated string little in the string big.
*/

char	*ft_strstr(const char *big, const char *little)
{
	size_t		blen;
	size_t		llen;

	blen = ft_strlen(big);
	llen = ft_strlen(little);
	while (blen >= llen)
	{
		if (*big == *little && !ft_memcmp(big, little, llen))
			return ((char *)big);
		++big;
		--blen;
	}
	return (NULL);
}
