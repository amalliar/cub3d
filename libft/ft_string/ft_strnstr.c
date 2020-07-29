/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 19:26:22 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:26:08 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** The ft_strnstr() function locates the first occurrence of the
** null-terminated string little in the string big, where not more
** than num characters are searched.
*/

char	*ft_strnstr(const char *big, const char *little, size_t num)
{
	char	bc;
	char	lc;
	size_t	len;

	if ((lc = *little++) != '\0')
	{
		len = ft_strlen(little);
		while (1)
		{
			while (1)
			{
				if (num-- == 0 || (bc = *big++) == '\0')
					return (NULL);
				if (bc == lc)
					break ;
			}
			if (len > num)
				return (NULL);
			if (!ft_strncmp(big, little, len))
				break ;
		}
		big--;
	}
	return ((char *)big);
}
