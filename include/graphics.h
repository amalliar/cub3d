/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:05:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/16 20:50:57 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# define BYTES_PER_PIXEL			4
# define FILE_HEADER_SIZE			14
# define INFO_HEADER_SIZE			40
# include "cub3d.h"
# include "mlx.h"

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_conv_data
{
	unsigned char	*file_header;
	unsigned char	*info_header;
	unsigned char	*img;
	int				fd;
	int				width_in_bytes;
	int				padding_size;
	int				stride;
}					t_conv_data;

int					mlx_image_to_bmp_file(t_mlx_image *mi, const char *name);
int					mlx_pixel_get(t_mlx_image *img, int x, int y);
void				mlx_pixel_fill(t_mlx_image *frame, int x, int y, int color);
void				drawline(t_mlx_image *frame, t_point p0, t_point p1, \
						int color);
void				drawverline(t_mlx_image *img, t_point p0, t_point p1, \
						int color);
void				drawhorline(t_mlx_image *img, t_point p0, t_point p1, \
						int color);
void				drawcircle(t_mlx_image *frame, t_point m, int r, int color);

#endif
