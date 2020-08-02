/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 21:12:41 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/03 00:18:40 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "X.h"
#include "Events.h"
#include "colors.h"
#include "graphics.h"
#include "ft_stdio.h"

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

int		keypress_handler(int keycode, t_data *data)
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
	}
	// TODO: Add color shifting depending on circle position within the image.
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

static int		render_next_frame(t_data *data)
{
	data->frame->img = mlx_new_image(data->frame->mlx, data->frame->img_width, \
		data->frame->img_height);
	data->frame->addr = mlx_get_data_addr(data->frame->img, &data->frame->bits_per_pixel, \
		&data->frame->line_length, &data->frame->endian);
	drawcircle_f(data->frame, data->circle->xm, data->circle->ym, data->circle->radius, \
		data->circle->color);
	mlx_put_image_to_window(data->frame->mlx, data->frame->win, data->frame->img, 0, 0);
	mlx_destroy_image(data->frame->mlx, data->frame->img);
	return (0);
}

static int		init_data(t_data *data)
{
	if (!(data->frame = (t_frame *)malloc(sizeof(t_frame))))
		return (1);
	if (!(data->circle = (t_circle *)malloc(sizeof(t_circle))))
		return (1);
	data->frame->mlx = mlx_init();
	data->frame->win_width = 512;
	data->frame->win_height = 512;
	data->frame->win = mlx_new_window(data->frame->mlx, data->frame->win_width, \
		data->frame->win_height, "cub3D");
	data->frame->img_width = data->frame->win_width;
	data->frame->img_height = data->frame->img_height;
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
	mlx_loop_hook(data.frame.mlx, render_next_frame, &data);
	mlx_hook (data.frame.win, KeyPress, KeyPressMask, keypress_handler, &data);
	mlx_loop(data.frame.mlx);
	return (0);
}
