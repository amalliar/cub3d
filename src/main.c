/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:38:20 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/04 18:46:44 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void		init_scene(t_scene *scene)
{
	if (((*scene).mlx_data.mlx = mlx_init()) == NULL)
		exit_failure("Failed creating mlx instance\n");
	(*scene).mlx_data.win = NULL;
	(*scene).textures.walls.north.img = NULL;
	(*scene).textures.walls.north.path = NULL;
	(*scene).textures.walls.south.img = NULL;
	(*scene).textures.walls.south.path = NULL;
	(*scene).textures.walls.west.img = NULL;
	(*scene).textures.walls.west.path = NULL;
	(*scene).textures.walls.east.img = NULL;
	(*scene).textures.walls.east.path = NULL;
	(*scene).sprites.item.img = NULL;
	(*scene).sprites.item.path = NULL;
}

int				main(int argc, char **argv)
{
	t_scene		scene;

	if (argc < 2)
		exit_failure("Program requires at least one argument (scene.cub)\n");
	init_scene(&scene);
	load_scene(&scene, argv[1]);
	// Render scene...
	return (0);
}
