/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:38:20 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/02 01:36:15 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "ft_string.h"

static void		init_scene(t_scene *scene)
{
	if (((*scene).mlx_data.mlx = mlx_init()) == NULL)
		exit_failure("Failed creating mlx instance\n");
	(*scene).mlx_data.width = MLX_WINDOW_WIDTH;
	(*scene).mlx_data.height = MLX_WINDOW_HEIGHT;
	(*scene).sprite_data.num_sprites = 0;
	(*scene).player_data.pos_x = -1;
	(*scene).player_data.level = 1;
	(*scene).keystates.kvk_ansi_w = KEY_UP;
	(*scene).keystates.kvk_ansi_a = KEY_UP;
	(*scene).keystates.kvk_ansi_s = KEY_UP;
	(*scene).keystates.kvk_ansi_d = KEY_UP;
	(*scene).keystates.kvk_leftarrow = KEY_UP;
	(*scene).keystates.kvk_rightarrow = KEY_UP;
	(*scene).mouse_grabbing = OFF;
}

int				main(int argc, char **argv)
{
	t_scene		scene;

	if (argc < 2)
		exit_failure("Program requires at least one argument (scene.cub)\n");
	if (argc > 3)
		exit_failure("Too many arguments\n");
	init_scene(&scene);
	load_scene(&scene, argv[1]);
	if (argc == 3)
	{
		if (!ft_strcmp("--save", argv[2]))
		{
			scene.render_mode = SCREENSHOT;
			render_scene(&scene, SCREENSHOT);
		}
		else
			exit_failure("Unknown argument: %s\n", argv[2]);
	}
	scene.render_mode = LOOP;
	render_scene(&scene, LOOP);
	return (0);
}
