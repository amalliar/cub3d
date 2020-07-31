/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 20:56:01 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/31 20:37:06 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "ft_stdlib.h"

void		mlx_pixel_fill(t_frame *frame, int x, int y, int color)
{
    char	*dst;

	dst = frame->addr + (y * frame->line_length + x * (frame->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
** Bresenham’s Line Algorithm for all octant line draws.
*/

void		drawline(t_frame *frame, int x0, int y0, int x1, int y1, int color)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;

	dx =  ft_abs(x1 - x0);
	sx = (x0 < x1) ? 1 : -1;
	dy = -ft_abs(y1 - y0);
	sy = (y0 < y1) ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		mlx_pixel_fill(frame, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

/*
** Midpoint Circle Algorithm.
*/

void		drawcircle(t_frame *frame, int xm, int ym, int r, int color)
{
	int		x;
	int		y;
	int		err;

	x = -r;
	y = 0;
	err = 2 - 2 * r;
	while (1)
	{
		mlx_pixel_fill(frame, xm - x, ym + y, color);
		mlx_pixel_fill(frame, xm - y, ym - x, color);
		mlx_pixel_fill(frame, xm + x, ym - y, color);
		mlx_pixel_fill(frame, xm + y, ym + x, color);
		r = err;
		if (r <= y)
			err += ++y * 2 + 1;
		if (r > x || err > y)
			err += ++x * 2 + 1;
		if (x >= 0)
			break ;
	}
}

void		drawellipse(t_frame *frame, int x0, int y0, int x1, int y1, int color)
{
	int a;
	int b;
	int b1;
	long dx;
	long dy;
	long err;
	long e2;

	a = ft_abs(x1 - x0);
	b = ft_abs(y1 - y0);
	b1 = b & 1;
	dx = 4 * (1 - a) * b * b;
	dy = 4 * (b1 + 1) * a * a;
	err = dx + dy + b1 * a * a;
	if (x0 > x1)
	{
		x0 = x1;
		x1 += a;
	}
	if (y0 > y1)
		y0 = y1;
	y0 += (b + 1) / 2;
	y1 = y0-b1;
	a *= 8 * a;
	b1 = 8 * b * b;
	while (1)
	{
		mlx_pixel_fill(frame, x1, y0, color);
		mlx_pixel_fill(frame, x0, y0, color);
		mlx_pixel_fill(frame, x0, y1, color);
		mlx_pixel_fill(frame, x1, y1, color);
		e2 = 2 * err;
		if (e2 <= dy)
		{
			++y0;
			--y1;
			dy += a;
			err += dy;
		}
		if (e2 >= dx || 2 * err > dy)
		{
			x0++;
			x1--;
			dx += b1;
			err += dx;
		}
		if (x0 > x1)
			break ;
	}
	while (y0 - y1 < b)
	{
		mlx_pixel_fill(frame, x0 - 1, y0, color);
		mlx_pixel_fill(frame, x1 + 1, y0++, color);
		mlx_pixel_fill(frame, x0 - 1, y1, color);
		mlx_pixel_fill(frame, x1 + 1, y1--, color);
	}
}

void		drawpoly(t_frame *frame, int numpoints, int *polypoints, int color)
{
	int		i;

	if (numpoints < 4 || \
		polypoints[0] != polypoints[numpoints * 2 - 2] || \
		polypoints[1] != polypoints[numpoints * 2 - 1])
		return ;
	i = 0;
	while (i < numpoints - 1)
	{
		drawline(frame, polypoints[i * 2], polypoints[i * 2 + 1], \
			polypoints[i * 2 + 2], polypoints[i * 2 + 3], color);
		++i;
	}
}
