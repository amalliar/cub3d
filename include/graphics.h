/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:05:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/13 19:33:47 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "cub3d.h"
# include "mlx.h"

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

int				mlx_pixel_get(t_mlx_image *img, int x, int y);
void			mlx_pixel_fill(t_mlx_image *frame, int x, int y, int color);
void			drawline(t_mlx_image *frame, t_point p0, t_point p1, int color);
void			drawcircle(t_mlx_image *frame, t_point m, int r, int color);

#endif
