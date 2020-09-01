/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 20:36:31 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/02 00:57:53 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void		swap(int *p0, int *p1)
{
	*p0 ^= *p1;
	*p1 ^= *p0;
	*p0 ^= *p1;
}

void			drawverline(t_mlx_image *img, t_point p0, t_point p1, int color)
{
	if (p0.x != p1.x)
		return ;
	if (p0.y > p1.y)
		swap(&p0.y, &p1.y);
	while (p0.y <= p1.y)
	{
		mlx_pixel_set(img, p0.x, p0.y, color);
		++p0.y;
	}
}

void			drawhorline(t_mlx_image *img, t_point p0, t_point p1, int color)
{
	if (p0.y != p1.y)
		return ;
	if (p0.x > p1.x)
		swap(&p0.x, &p1.x);
	while (p0.x <= p1.x)
	{
		mlx_pixel_set(img, p0.x, p0.y, color);
		++p0.x;
	}
}

void			latch_image(t_mlx_image *dst, t_mlx_image *src, \
					t_point p0, double scale)
{
	t_point		draw_end;
	double		tex_x;
	double		tex_y;
	double		step;
	int			start_x;

	step = 1.0 / scale;
	draw_end.x = p0.x + (int)(src->width * scale);
	draw_end.y = p0.y + (int)(src->height * scale);
	start_x = p0.x;
	tex_y = 0;
	while (p0.y < draw_end.y)
	{
		p0.x = start_x;
		tex_x = 0;
		while (p0.x < draw_end.x)
		{
			mlx_pixel_set(dst, p0.x, p0.y, mlx_pixel_get(src, \
				(int)tex_x, (int)tex_y));
			tex_x += step;
			++p0.x;
		}
		tex_y += step;
		++p0.y;
	}
}

void			latch_number(t_mlx_image *dst, t_mlx_image *src, \
					int nbr, t_point p0)
{
	if (nbr == 0)
	{
		latch_image(dst, src, p0, HUD_SCALE);
		return ;
	}
	while (nbr > 0)
	{
		latch_image(dst, src + nbr % 10, p0, HUD_SCALE);
		nbr /= 10;
		p0.x -= 8 * HUD_SCALE;
	}
}
