/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:07:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/17 15:15:14 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

int		clr_create(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int		clr_get_alpha(int color)
{
	return ((color & (0xFF << 24)) >> 24);
}

int		clr_get_red(int color)
{
	return ((color & (0xFF << 16)) >> 16);
}

int		clr_get_green(int color)
{
	return ((color & (0xFF << 8)) >> 8);
}

int		clr_get_blue(int color)
{
	return (color & 0xFF);
}
