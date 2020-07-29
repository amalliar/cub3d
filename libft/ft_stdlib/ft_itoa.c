/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:49:55 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/15 01:22:58 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

/*
** Allocates and returns a string representing the
** integer received as an argument.
*/

static void		init_vars(intmax_t num, intmax_t *orig, \
					short *digits)
{
	*orig = num;
	*digits = (num == 0) ? 1 : 0;
}

char			*ft_itoa(intmax_t num, int base)
{
	intmax_t	orig;
	short		digits;
	char		*beg;
	char		*end;

	if (base < 2 || base > 16)
		return (NULL);
	init_vars(num, &orig, &digits);
	while (num != 0)
	{
		++digits;
		num /= base;
	}
	if (!(beg = (char *)malloc((orig < 0) + digits + 1)))
		return (NULL);
	*beg = (orig == 0) ? '0' : '-';
	end = beg + (orig < 0) + digits;
	*end-- = '\0';
	num = (orig < 0) ? -1 : 1;
	while (orig != 0)
	{
		*end-- = "0123456789abcdef"[orig % base * num];
		orig /= base;
	}
	return (beg);
}
