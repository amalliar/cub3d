/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 05:43:35 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/17 06:16:11 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_ctype.h"

/*
** Converts the string to lowercase in place.
*/

char	*ft_strtolower(char *str)
{
	char	*beg;

	beg = str;
	while (*str)
	{
		if (ft_isupper(*str))
			*str = ft_tolower(*str);
		++str;
	}
	return (beg);
}
