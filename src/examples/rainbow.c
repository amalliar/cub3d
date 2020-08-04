/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:15:08 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/03 18:38:33 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "graphics.h"
#include "X.h"
#include "Events.h"

static void		destroy_data(t_frame *frame)
{
	mlx_destroy_window(frame->mlx, frame->win);
}

static int		keypress_handler(int keycode, t_frame *frame)
{
	if (keycode == kVK_Escape)
	{
		destroy_data(frame);
		exit(0);
	}
}

static int		render_next_frame(t_frame *frame)
{
	int		y;
	int		r;
	int		g;
	int		b;

	frame->img = mlx_new_image(frame->mlx, frame->img_width, frame->img_height);
	frame->addr = mlx_get_data_addr(frame->img, &frame->bits_per_pixel, \
		&frame->line_length, &frame->endian);
	y = 0;
	while (y < frame->img_height)
	{
		drawline(frame, 0, y, frame->img_width - 1, y, frame->color);
		++y;
	}
	mlx_put_image_to_window(frame->mlx, frame->win, frame->img, 0, 0);
	mlx_destroy_image(frame->mlx, frame->img);
	r = get_red(frame->color);
	g = get_green(frame->color);
	b = get_blue(frame->color);
	if (r == 0xFF && g < 0xFF && b == 0)
		++g;
	else if (r > 0 && g == 0xFF && b == 0)
		--r;
	else if (r == 0 && g == 0xFF && b < 0xFF)
		++b;
	else if (r == 0 && g > 0 && b == 0xFF)
		--g;
	else if (r < 0xFF && g == 0 && b == 0xFF)
		++r;
	else if (r == 0xFF && g == 0 && b > 0)
		--b;
	frame->color = create_color(0, r, g, b);
	return (0);
}

int				main(void)
{
	t_frame		frame;

	frame.mlx = mlx_init();
	frame.win_width = 1920;
	frame.win_height = 1080;
	frame.win = mlx_new_window(frame.mlx, frame.win_width, frame.win_height, "cub3D");
	frame.img_width = frame.win_width;
	frame.img_height = frame.win_height;
	frame.color = RED;
	mlx_loop_hook(frame.mlx, render_next_frame, &frame);
	mlx_hook (frame.win, KeyPress, KeyPressMask, keypress_handler, &frame);
	mlx_loop(frame.mlx);
	return (0);
}
