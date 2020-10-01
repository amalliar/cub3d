/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:38:20 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/01 14:18:26 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "ft_string.h"

static void		init_mlx_data(t_mlx_data *mlx_data)
{
	if (!(mlx_data->mlx = mlx_init()))
		exit_failure("Failed creating mlx instance\n");
	mlx_data->win = NULL;
	(mlx_data->frame).img = NULL;
	mlx_data->width = 0;
	mlx_data->height = 0;
}

static void		init_keystates(t_keystates *ks)
{
	ks->kvk_ansi_w = KEY_UP;
	ks->kvk_ansi_a = KEY_UP;
	ks->kvk_ansi_s = KEY_UP;
	ks->kvk_ansi_d = KEY_UP;
	ks->kvk_leftarrow = KEY_UP;
	ks->kvk_rightarrow = KEY_UP;
}

static void		init_scene(t_scene *scene)
{
	init_mlx_data(&scene->mlx_data);
	init_keystates(&scene->keystates);
	(scene->textures).walls.north.img = NULL;
	(scene->textures).walls.south.img = NULL;
	(scene->textures).walls.west.img = NULL;
	(scene->textures).walls.east.img = NULL;
	(scene->textures).sprite.img = NULL;
	(scene->sprite_data).num_sprites = 0;
	(scene->player_data).pos_x = -1;
	(scene->player_data).move_speed = PLAYER_MOVE_SPEED;
	(scene->player_data).rot_speed = PLAYER_ROT_SPEED;
	(scene->colors).floor = -1;
	(scene->colors).ceilling = -1;
}

int				main(int argc, char **argv)
{
	t_scene		scene;

	if (argc < 2)
		exit_failure("Program requires at least one argument (scene.cub)\n");
	if (!ft_strmatch("*.cub", argv[1]))
		exit_failure("Unknown file type: %s\n", argv[1]);
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
