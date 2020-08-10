/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 21:12:41 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/03 18:36:18 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "X.h"
#include "Events.h"
#include "colors.h"
#include "graphics.h"
#define MLX_SYNC_IMAGE_WRITABLE    1
#define MLX_SYNC_WIN_FLUSH_CMD     2
#define MLX_SYNC_WIN_CMD_COMPLETED 3

typedef struct	s_circle
{
	int			xm;
	int			ym;
	int			radius;
	int			color;
}				t_circle;

typedef struct	s_data
{
	t_frame		*frame;
	t_circle	*circle;
}				t_data;

static void		shift_circle_color(t_data *data)
{
	int		xm;
	int		ym;
	int		center_dist;
	int		center_dist_limit;
	int		max_dist;
	int		r;
	int		g;

	xm = data->frame->img_width / 2;
	ym = data->frame->img_height / 2;
	center_dist = sqrt(pow(xm - data->circle->xm, 2) + pow(ym - data->circle->ym, 2));
	center_dist_limit = sqrt(2) * data->circle->radius;
	max_dist = sqrt(pow(data->frame->img_width, 2) + pow(data->frame->img_height, 2)) / 2 - center_dist_limit;
	r = 255 * center_dist / max_dist;
	g = 255 - r;
	data->circle->color = create_color(0, r, g, 0);
}

static void		destroy_data(t_data *data)
{
	mlx_destroy_image(data->frame->mlx, data->frame->img);
	mlx_destroy_window(data->frame->mlx, data->frame->win);
	free(data->frame);
	free(data->circle);
}

static int		keypress_handler(int keycode, t_data *data)
{
	switch (keycode)
	{
		case kVK_ANSI_W:
			if (data->circle->ym - data->circle->radius > 1)
				data->circle->ym -= 1;
			break ;
		case kVK_ANSI_A:
			if (data->circle->xm - data->circle->radius > 1)
				data->circle->xm -= 1;
			break ;
		case kVK_ANSI_S:
			if (data->circle->ym + data->circle->radius < data->frame->img_height - 1)
				data->circle->ym += 1;
			break ;
		case kVK_ANSI_D:
			if (data->circle->xm + data->circle->radius < data->frame->img_width - 1)
				data->circle->xm += 1;
			break ;
		case kVK_Escape:
			destroy_data(data);
			exit(0);
			break ;
	}
	shift_circle_color(data);
	return (0);
}

static void		drawcircle_f(t_frame *frame, int xm, int ym, int r, int clr)
{
	while (r >= 0)
	{
		drawcircle(frame, xm, ym, r, clr);
		--r;
	}
}

static void		clear_image(t_frame *frame, int color)
{
	int		x;
	int		y;

	y = 0;
	while (y < frame->img_height)
	{
		x = 0;
		while (x < frame->img_width)
		{
			mlx_pixel_fill(frame, x, y, color);
			++x;
		}
		++y;
	}
}

static int		render_next_frame(t_data *data)
{
	clear_image(data->frame, BLACK);
	drawcircle_f(data->frame, data->circle->xm, data->circle->ym, data->circle->radius, \
		data->circle->color);
	mlx_put_image_to_window(data->frame->mlx, data->frame->win, data->frame->img, 0, 0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, data->frame->win);
	return (0);
}

static int		init_data(t_data *data)
{
	if (!(data->frame = (t_frame *)malloc(sizeof(t_frame))))
		return (1);
	if (!(data->circle = (t_circle *)malloc(sizeof(t_circle))))
		return (1);
	if (!(data->frame->mlx = mlx_init()))
		return (1);
	data->frame->win_width = 512;
	data->frame->win_height = 512;
	if (!(data->frame->win = mlx_new_window(data->frame->mlx, data->frame->win_width, \
		data->frame->win_height, "cub3D")))
		return (1);
	data->frame->img_width = data->frame->win_width;
	data->frame->img_height = data->frame->win_height;
	if (!(data->frame->img = mlx_new_image(data->frame->mlx, data->frame->img_width, \
		data->frame->img_height)))
		return (1);
	data->frame->addr = mlx_get_data_addr(data->frame->img, &data->frame->bits_per_pixel, \
		&data->frame->line_length, &data->frame->endian);
	data->circle->xm = data->frame->img_width / 2;
	data->circle->ym = data->frame->img_height / 2;
	data->circle->radius = (data->frame->img_width < data->frame->img_height) ? \
		data->frame->img_width / 10 : data->frame->img_height / 10;
	data->circle->color = LIME;
	return (0);
}

int				main(void)
{
	t_data		data;

	if (init_data(&data))
		return (1);
	mlx_loop_hook(data.frame->mlx, render_next_frame, &data);
	mlx_hook (data.frame->win, KeyPress, KeyPressMask, keypress_handler, &data);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data.frame->img);
	mlx_loop(data.frame->mlx);
	return (0);
}