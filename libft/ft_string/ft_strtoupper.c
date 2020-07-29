/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 05:43:35 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/17 05:46:09 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_ctype.h"

/*
** Converts the string to uppercase in place.
*/

char	*ft_strtoupper(char *str)
{
	char	*beg;

	beg = str;
	while (*str)
	{
		if (ft_islower(*str))
			*str = ft_toupper(*str);
		++str;
	}
	return (beg);
}
