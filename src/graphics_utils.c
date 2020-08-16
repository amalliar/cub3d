/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 20:36:31 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/16 20:44:28 by amalliar         ###   ########.fr       */
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
		mlx_pixel_fill(img, p0.x, p0.y, color);
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
		mlx_pixel_fill(img, p0.x, p0.y, color);
		++p0.x;
	}
}
