/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 01:09:16 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 03:03:41 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "cub3d.h"

int		clr_mix(int color1, int color2, double amount)
{
	t_point		red;
	t_point		green;
	t_point		blue;

	if (amount < 0 || amount > 1)
		return (color1);
	red.x = clr_get_red(color1);
	red.y = clr_get_red(color2);
	green.x = clr_get_green(color1);
	green.y = clr_get_green(color2);
	blue.x = clr_get_blue(color1);
	blue.y = clr_get_blue(color2);
	return (clr_create(0, \
			(1 - amount) * red.x + amount * red.y, \
			(1 - amount) * green.x + amount * green.y, \
			(1 - amount) * blue.x + amount * blue.y));
}
