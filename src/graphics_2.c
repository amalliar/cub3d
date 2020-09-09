/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 20:36:31 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/09 18:27:26 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "colors.h"

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

/*
** Scales and copies mlx_image *src to mlx_image *dst, p0 is the
** upper left corner from which the image is drawn.
*/

void			latch_image(t_mlx_image *dst, t_mlx_image *src, \
					t_point p0, double scale)
{
	t_point		draw_end;
	t_fpoint	tex;
	double		step;
	int			start_x;
	int			color;

	step = 1.0 / scale;
	draw_end.x = p0.x + (int)(src->width * scale);
	draw_end.y = p0.y + (int)(src->height * scale);
	start_x = p0.x;
	tex.y = 0;
	while (p0.y < draw_end.y)
	{
		p0.x = start_x;
		tex.x = 0;
		while (p0.x < draw_end.x)
		{
			if ((color = mlx_pixel_get(src, (int)tex.x, (int)tex.y)) != INVIS)
				mlx_pixel_set(dst, p0.x, p0.y, color);
			tex.x += step;
			++p0.x;
		}
		tex.y += step;
		++p0.y;
	}
}

/*
** Latches given number to an mlx_image *dst, p0 is the
** upper left corner from which the last digit is drawn.
**
** The rest of the digits are shifted to the right.
*/

void			latch_number(t_mlx_image *dst, t_mlx_image *arr, \
					int nbr, t_point p0)
{
	if (nbr == 0)
	{
		latch_image(dst, arr, p0, HUD_SCALE);
		return ;
	}
	while (nbr > 0)
	{
		latch_image(dst, arr + nbr % 10, p0, HUD_SCALE);
		nbr /= 10;
		p0.x -= 8 * HUD_SCALE;
	}
}
