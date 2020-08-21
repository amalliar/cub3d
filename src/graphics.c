/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 20:56:01 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/21 20:21:23 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "ft_stdlib.h"

int				mlx_pixel_get(t_mlx_image *img, int x, int y)
{
	int		*dst;

	dst = (int *)(img->addr + (y * img->line_size + \
		x * (img->bits_per_pixel / 8)));
	return (*dst);
}

void			mlx_pixel_set(t_mlx_image *img, int x, int y, int color)
{
	int		*dst;

	dst = (int *)(img->addr + (y * img->line_size + \
		x * (img->bits_per_pixel / 8)));
	*dst = color;
}

static void		init_delta_step(t_point *p0, t_point *p1, \
					t_point *d, t_point *s)
{
	d->x = ft_abs(p1->x - p0->x);
	s->x = (p0->x < p1->x) ? 1 : -1;
	d->y = -ft_abs(p1->y - p0->y);
	s->y = (p0->y < p1->y) ? 1 : -1;
}

void			drawline(t_mlx_image *img, t_point p0, t_point p1, int color)
{
	t_point		d;
	t_point		s;
	int			err;
	int			e2;

	init_delta_step(&p0, &p1, &d, &s);
	err = d.x + d.y;
	while (1)
	{
		mlx_pixel_set(img, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = 2 * err;
		if (e2 >= d.y)
		{
			err += d.y;
			p0.x += s.x;
		}
		if (e2 <= d.x)
		{
			err += d.x;
			p0.y += s.y;
		}
	}
}

void			drawcircle(t_mlx_image *img, t_point m, int r, int color)
{
	int		x;
	int		y;
	int		err;

	x = -r;
	y = 0;
	err = 2 - 2 * r;
	while (1)
	{
		mlx_pixel_set(img, m.x - x, m.y + y, color);
		mlx_pixel_set(img, m.x - y, m.y - x, color);
		mlx_pixel_set(img, m.x + x, m.y - y, color);
		mlx_pixel_set(img, m.x + y, m.y + x, color);
		r = err;
		if (r <= y)
			err += ++y * 2 + 1;
		if (r > x || err > y)
			err += ++x * 2 + 1;
		if (x >= 0)
			break ;
	}
}
