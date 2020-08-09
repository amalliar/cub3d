/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:38:20 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/09 19:53:03 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "ft_stdio.h"
#include "ft_string.h"

static void		init_scene(t_scene *scene)
{
	if (((*scene).mlx_data.mlx = mlx_init()) == NULL)
		exit_failure("Failed creating mlx instance\n");
	(*scene).mlx_data.win = NULL;
	(*scene).mlx_data.frame.img = NULL;
	(*scene).mlx_data.width = 0;
	(*scene).mlx_data.height = 0;
	(*scene).textures.walls.north.img = NULL;
	(*scene).textures.walls.south.img = NULL;
	(*scene).textures.walls.west.img = NULL;
	(*scene).textures.walls.east.img = NULL;
	(*scene).sprites.item.img = NULL;
	(*scene).player_data.pos_x = -1;
	(*scene).player_data.move_speed = PLAYER_MOVE_SPEED;
	(*scene).player_data.rot_speed = PLAYER_ROT_SPEED;
	(*scene).keystates.kvk_ansi_w = KEY_UP;
	(*scene).keystates.kvk_ansi_a = KEY_UP;
	(*scene).keystates.kvk_ansi_s = KEY_UP;
	(*scene).keystates.kvk_ansi_d = KEY_UP;
	(*scene).keystates.kvk_leftarrow = KEY_UP;
	(*scene).keystates.kvk_rightarrow = KEY_UP;

}

static void		print_map(t_map_data *map_data)
{
	int		y;

	y = 0;
	while (y < map_data->height)
	{
		ft_printf("%s\n", (map_data->map)[y]);
		++y;
	}
}

static void		print_scene_data(t_scene *scene)
{
	ft_printf("Scene Configuration:\n");
	ft_printf("Resolution is              %dx%d\n", (*scene).mlx_data.width, (*scene).mlx_data.height);
	ft_printf("North wall texture size is %dx%d\n", (*scene).textures.walls.north.width, (*scene).textures.walls.north.height);
	ft_printf("South wall texture size is %dx%d\n", (*scene).textures.walls.south.width, (*scene).textures.walls.south.height);
	ft_printf("West wall texture size is  %dx%d\n", (*scene).textures.walls.west.width, (*scene).textures.walls.west.height);
	ft_printf("East wall texture size is  %dx%d\n", (*scene).textures.walls.east.width, (*scene).textures.walls.east.height);
	ft_printf("Sprite size is             %dx%d\n", (*scene).sprites.item.width, (*scene).sprites.item.height);
	ft_printf("Floor color is             %#x\n", (*scene).colors.floor);
	ft_printf("Ceilling color is          %#x\n", (*scene).colors.ceilling);
	ft_printf("Map size is                %dx%d\n", (*scene).map_data.width, (*scene).map_data.height);
	ft_printf("\n");
	print_map(&(*scene).map_data);
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
	//print_scene_data(&scene);
	if (argc == 3) 
	{
		if (!ft_strcmp("--save", argv[2]))
		{
			//screenshot();
			exit(EXIT_SUCCESS);
		}
		else
			exit_failure("Unknown parameter: %s", argv[2]);
	}
	render_scene(&scene);
	return (0);
}
