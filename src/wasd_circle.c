/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 21:12:41 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/01 17:07:17 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "X.h"
#include "Events.h"
#include "colors.h"
#include "graphics.h"
#include "ft_stdio.h"

typedef struct	s_circle
{
	int			x_pos;
	int			y_pos;
	int			radius;
	int			color;
}				t_circle;

typedef struct	s_game_state
{
	t_frame		frame;
	t_circle	circle;
}				t_game_state;

int		keypress_handler(int keycode, t_game_state *game)
{
	switch (keycode)
	{
		case kVK_ANSI_W:
			if ((game->circle).y_pos - (game->circle).radius > 1)
				(game->circle).y_pos -= 1;
			break ;
		case kVK_ANSI_A:
			if ((game->circle).x_pos - (game->circle).radius > 1)
				(game->circle).x_pos -= 1;
			break ;
		case kVK_ANSI_S:
			if ((game->circle).y_pos + (game->circle).radius < (game->frame).img_height - 1)
				(game->circle).y_pos += 1;
			break ;
		case kVK_ANSI_D:
			if ((game->circle).x_pos + (game->circle).radius < (game->frame).img_width - 1)
				(game->circle).x_pos += 1;
			break ;
	}
	// shift_color(game);
	return (0);
}

int		render_next_frame(t_game_state *game)
{

	int		r;

	(game->frame).img = mlx_new_image((game->frame).mlx, (game->frame).img_width, \
		(game->frame).img_height);
	(game->frame).addr = mlx_get_data_addr((game->frame).img, &(game->frame).bits_per_pixel, \
		&(game->frame).line_length, &(game->frame).endian);
	r = (game->circle).radius;
	while (r >= 0)
	{
		drawcircle(&game->frame, (game->circle).x_pos, (game->circle).y_pos, \
			r, (game->circle).color);
		--r;
	}
	mlx_put_image_to_window((game->frame).mlx, (game->frame).win, (game->frame).img, 0, 0);
	mlx_destroy_image((game->frame).mlx, (game->frame).img);
	return (0);
}

int		main(void)
{
	t_game_state	game;

	game.frame.mlx = mlx_init();
	game.frame.win_width = 512;
	game.frame.win_height = 512;
	game.frame.win = mlx_new_window(game.frame.mlx, game.frame.win_width, \
		game.frame.win_height, "cub3D");
	game.frame.img_width = game.frame.win_width;
	game.frame.img_height = game.frame.win_height;
	game.frame.color = RED;
	game.circle.x_pos = game.frame.img_width / 2;
	game.circle.y_pos = game.frame.img_height / 2;
	if (game.frame.img_width < game.frame.img_height)
		game.circle.radius = game.frame.img_width / 10;
	else
		game.circle.radius = game.frame.img_height / 10;
	game.circle.color = LIME;
	mlx_loop_hook(game.frame.mlx, render_next_frame, &game);
	mlx_hook (game.frame.win, KeyPress, KeyPressMask, keypress_handler, &game);
	mlx_loop(game.frame.mlx);
	return (0);
}
