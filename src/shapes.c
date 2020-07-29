/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 20:56:01 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/29 22:00:35 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_rectangle(t_frame *frame, int x, int y, int width, int height, int color)
{
	int		i;
	int		j;

	j = y;
	while (j < y + height)
	{
		i = x;
		while (i < x + width)
		{
			mlx_pixel_fill(frame, i, j, color);
			++i;
		}
		++j;
	}
}

void		drawline(int x1, int y1, int x2, int y2)
{
	return ;
}

void		drawpoly(int number, int *polypoints)
{
	return ;
}
