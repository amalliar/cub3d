/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:05:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/30 19:41:53 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include <mlx.h>
# include <math.h>

typedef struct	s_frame
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			img_width;
	int			img_height;
}				t_frame;

void	mlx_pixel_fill(t_frame *frame, int x, int y, int color);
void	draw_rectangle(t_frame *frame, int x, int y, int width, int height, int color);
void	drawcircle(t_frame *frame, int xm, int ym, int r, int color);
void	drawellipse(t_frame *frame, int x0, int y0, int x1, int y1, int color);
void	drawline(t_frame *frame, int x0, int y0, int x1, int y1, int color);
void	drawpoly(t_frame *frame, int numpoints, int *polypoints, int color);

#endif
