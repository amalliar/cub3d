/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 21:23:53 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/21 23:30:32 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "textures.h"

static void		load_walls(t_scene *scene)
{
	t_mlx_image		*walls;
	int				i;

	walls = (*scene).textures.walls;
	i = 0;
	while (i < NUM_WALL_TEXTURES)
	{
		if (!(walls[i].img = mlx_xpm_file_to_image((*scene).mlx_data.mlx, \
			g_wall_texture_paths[i], &walls[i].width, &walls[i].height)))
			exit_failure("Failed creating mlx image instance from file: %s\n", \
				g_wall_texture_paths[i]);
		walls[i].addr = mlx_get_data_addr(walls[i].img, \
			&walls[i].bits_per_pixel, &walls[i].line_size, &walls[i].endian);
		++i;
	}
}

static void		load_objects(t_scene *scene)
{
	t_mlx_image		*objects;
	int				i;

	objects = (*scene).textures.objects;
	i = 0;
	while (i < NUM_OBJECT_TEXTURES)
	{
		if (!(objects[i].img = mlx_xpm_file_to_image((*scene).mlx_data.mlx, \
			g_object_texture_paths[i], &objects[i].width, &objects[i].height)))
			exit_failure("Failed creating mlx image instance from file: %s\n", \
				g_object_texture_paths[i]);
		objects[i].addr = mlx_get_data_addr(objects[i].img, \
			&objects[i].bits_per_pixel, &objects[i].line_size, \
			&objects[i].endian);
		++i;
	}
}

void			load_textures(t_scene *scene)
{
	load_walls(scene);
	load_objects(scene);
}
