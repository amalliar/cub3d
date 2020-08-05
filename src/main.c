/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:38:20 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/05 22:53:01 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "ft_stdio.h"

static void		init_scene(t_scene *scene)
{
	if (((*scene).mlx_data.mlx = mlx_init()) == NULL)
		exit_failure("Failed creating mlx instance\n");
	(*scene).mlx_data.win = NULL;
	(*scene).textures.walls.north.img = NULL;
	(*scene).textures.walls.south.img = NULL;
	(*scene).textures.walls.west.img = NULL;
	(*scene).textures.walls.east.img = NULL;
	(*scene).sprites.item.img = NULL;
	(*scene).player_data.orientation = 0;
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
	init_scene(&scene);
	load_scene(&scene, argv[1]);
	print_scene_data(&scene);
	// Render scene...
	return (0);
}
