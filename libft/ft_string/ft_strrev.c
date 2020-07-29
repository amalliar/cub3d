/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 03:08:10 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/17 06:33:55 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Reverses the string in place.
*/

char	*ft_strrev(char *str)
{
	char	*beg;
	char	*end;

	beg = str;
	end = beg + ft_strlen(str) - 1;
	while (beg < end)
	{
		*beg ^= *end;
		*end ^= *beg;
		*beg ^= *end;
		++beg;
		--end;
	}
	return (str);
}
