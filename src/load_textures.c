/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 21:23:53 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/01 06:48:11 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "textures.h"

static void		int_load_textures(t_scene *scene, t_mlx_image *arr, \
					char (*paths)[128], int num_textures)
{
	int				i;

	i = 0;
	while (i < num_textures)
	{
		if (!(arr[i].img = mlx_xpm_file_to_image((*scene).mlx_data.mlx, \
			paths[i], &arr[i].width, &arr[i].height)))
			exit_failure("Failed creating mlx image instance from file: %s\n", \
				paths[i]);
		arr[i].addr = mlx_get_data_addr(arr[i].img, &arr[i].bits_per_pixel, \
			&arr[i].line_size, &arr[i].endian);
		++i;
	}
}

void			load_textures(t_scene *scene)
{
	int_load_textures(scene, (*scene).textures.walls, \
		g_wall_texture_paths, NUM_WALL_TEXTURES);
	int_load_textures(scene, (*scene).textures.objects, \
		g_object_texture_paths, NUM_OBJECT_TEXTURES);
	int_load_textures(scene, (*scene).textures.hud, \
		g_hud_texture_paths, NUM_HUD_TEXTURES);
}
