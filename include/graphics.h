/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:05:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/07 17:43:31 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "cub3d.h"
# include "mlx.h"
# include "ft_stdlib.h"

void	mlx_pixel_fill(t_mlx_image *frame, int x, int y, int color);
void	draw_rectangle(t_mlx_image *frame, int x, int y, int width, int height, int color);
void	drawcircle(t_mlx_image *frame, int xm, int ym, int r, int color);
void	drawellipse(t_mlx_image *frame, int x0, int y0, int x1, int y1, int color);
void	drawline(t_mlx_image *frame, int x0, int y0, int x1, int y1, int color);
void	drawverline(t_mlx_image *frame, int x, int y0, int y1, int color);
void	drawpoly(t_mlx_image *frame, int numpoints, int *polypoints, int color);

#endif
