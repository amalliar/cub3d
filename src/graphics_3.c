/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:14:44 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 03:12:58 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "graphics.h"

static inline double	det(double a, double b, double c, double d)
{
	return (a * d - b * c);
}

bool					intersect(t_line *m, t_line *n, t_fpoint *res)
{
	double		zn;

	zn = det(m->a, m->b, n->a, n->b);
	if (fabs(zn) < DBL_EPSILON)
		return (false);
	res->x = -det(m->c, m->b, n->c, n->b) / zn;
	res->y = -det(m->a, m->c, n->a, n->c) / zn;
	return (true);
}

void					segment_to_line(t_segment *segm, t_line *line)
{
	line->a = (*segm).p0.y - (*segm).p1.y;
	line->b = (*segm).p1.x - (*segm).p0.x;
	line->c = (*segm).p0.x * (*segm).p1.y - (*segm).p1.x * (*segm).p0.y;
}

void					add_color_mask(t_mlx_image *frame, t_point res, \
							int color, double opacity)
{
	int		old_color;
	int		x;
	int		y;

	y = 0;
	while (y < res.y)
	{
		x = 0;
		while (x < res.x)
		{
			old_color = mlx_pixel_get(frame, x, y);
			old_color = clr_mix(old_color, color, opacity);
			mlx_pixel_set(frame, x, y, old_color);
			++x;
		}
		++y;
	}
}
