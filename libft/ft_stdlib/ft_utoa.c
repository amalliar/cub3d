/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:49:55 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/14 00:29:08 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

/*
** Allocates and returns a string representing the
** integer received as an argument.
*/

char	*ft_utoa(uintmax_t num, int base)
{
	uintmax_t	orig;
	short		digits;
	char		*beg;
	char		*end;

	if (base < 2 || base > 16)
		return (NULL);
	orig = num;
	digits = (num == 0) ? 1 : 0;
	while (num != 0)
	{
		++digits;
		num /= base;
	}
	if (!(beg = (char *)malloc(digits + 1)))
		return (NULL);
	*beg = '0';
	end = beg + digits;
	*end-- = '\0';
	while (orig != 0)
	{
		*end-- = "0123456789abcdef"[orig % base];
		orig /= base;
	}
	return (beg);
}
