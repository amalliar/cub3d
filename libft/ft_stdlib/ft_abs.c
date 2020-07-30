/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:25:18 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/30 18:53:30 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

/*
** Computes the absolute value of the integer num.
*/

int		ft_abs(int num)
{
	return ((num < 0 && num > INT_MIN) ? -num : num);
}
