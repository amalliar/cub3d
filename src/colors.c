/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:07:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/13 18:06:46 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

int		create_color(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int		get_alpha(int color)
{
	return ((color & (0xFF << 24)) >> 24);
}

int		get_red(int color)
{
	return ((color & (0xFF << 16)) >> 16);
}

int		get_green(int color)
{
	return ((color & (0xFF << 8)) >> 8);
}

int		get_blue(int color)
{
	return (color & 0xFF);
}
