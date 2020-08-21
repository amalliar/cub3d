/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:35:55 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/21 21:27:04 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_scene.h"
#include "ft_string.h"
#include "ft_stdlib.h"

static void		set_player_dir(t_player_data *pd, double dir_x, double dir_y)
{
	pd->dir_x = dir_x;
	pd->dir_y = dir_y;
}

static void		set_plane_dir(t_player_data *pd, double plane_x, double plane_y)
{
	pd->plane_x = plane_x;
	pd->plane_y = plane_y;
}

static void		load_player_data(t_player_data *player_data, int x, int y, \
					char obj)
{
	if (player_data->pos_x != -1)
		exit_failure("Double initialisation of player's start position\n");
	player_data->pos_x = x + 0.5;
	player_data->pos_y = y + 0.5;
	if (obj == 'N')
	{
		set_player_dir(player_data, 0, -1);
		set_plane_dir(player_data, tan(PLAYER_FOV * M_PI / 360), 0);
	}
	else if (obj == 'S')
	{
		set_player_dir(player_data, 0, 1);
		set_plane_dir(player_data, -tan(PLAYER_FOV * M_PI / 360), 0);
	}
	else if (obj == 'E')
	{
		set_player_dir(player_data, 1, 0);
		set_plane_dir(player_data, 0, tan(PLAYER_FOV * M_PI / 360));
	}
	else if (obj == 'W')
	{
		set_player_dir(player_data, -1, 0);
		set_plane_dir(player_data, 0, -tan(PLAYER_FOV * M_PI / 360));
	}
}

static void		process_map_object(t_scene *scene, int x, int y, char obj)
{
	if (!ft_strchr(OUTER_MAP_OBJECTS, obj))
		check_neighbours(&(*scene).map_data, x, y);
	if (ft_strchr("NSEW", obj))
	{
		load_player_data(&(*scene).player_data, x, y, obj);
		((*scene).map_data.map)[y][x] = '0';
	}
	/*
	if (obj == '2')
	{
		if (!((*scene).sprites = ft_realloc((*scene).sprites, \
			(*scene).sprite_data.num_sprites * sizeof(t_sprite), \
			((*scene).sprite_data.num_sprites + 1) * sizeof(t_sprite))))
			exit_failure("%s\n", strerror(errno));
		((*scene).sprites)[(*scene).sprite_data.num_sprites].x = x + 0.5;
		((*scene).sprites)[(*scene).sprite_data.num_sprites].y = y + 0.5;
		(*scene).sprite_data.num_sprites += 1;
	}
	*/
}

void			parse_map(t_scene *scene)
{
	int		x;
	int		y;
	char	obj;

	y = 0;
	while (y < (*scene).map_data.height)
	{
		x = 0;
		while (x < (*scene).map_data.width)
		{
			obj = (*scene).map_data.map[y][x];
			if (!ft_strchr(DEFINED_MAP_OBJECTS, obj))
				exit_failure("Invalid map object at position [%s][%s]: %c\n", \
				ft_itoa(x, 10), ft_itoa(y, 10), obj);
			process_map_object(scene, x, y, obj);
			++x;
		}
		++y;
	}
	if ((*scene).player_data.pos_x == -1)
		exit_failure("Map is missing player's start position\n");
}
