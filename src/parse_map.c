/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:35:55 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 05:49:36 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_scene.h"
#include "parse_map.h"

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
	player_data->pos_z = 0;
	if (obj == '^')
	{
		set_player_dir(player_data, 0, -1);
		set_plane_dir(player_data, tan(PL_FOV * M_PI / 360), 0);
	}
	else if (obj == '_')
	{
		set_player_dir(player_data, 0, 1);
		set_plane_dir(player_data, -tan(PL_FOV * M_PI / 360), 0);
	}
	else if (obj == '>')
	{
		set_player_dir(player_data, 1, 0);
		set_plane_dir(player_data, 0, tan(PL_FOV * M_PI / 360));
	}
	else if (obj == '<')
	{
		set_player_dir(player_data, -1, 0);
		set_plane_dir(player_data, 0, -tan(PL_FOV * M_PI / 360));
	}
}

static void		process_map_object(t_scene *scene, int x, int y, char obj)
{
	if (ft_strchr(MP_INNER_OBJECTS, obj))
		check_neighbours(&scene->map_data, x, y);
	if (ft_strchr("^_<>", obj))
	{
		load_player_data(&scene->player_data, x, y, obj);
		((scene->map_data).map)[y][x] = '0';
	}
	else if (ft_strchr(MP_OBJECTS, obj))
		load_object_data(scene, x, y, obj);
	else if (ft_strchr(MP_ENEMIES, obj))
		load_enemie_data(scene, x, y, obj);
	else if (ft_strchr(MP_DOORS, obj))
		load_door_data(scene, x, y, obj);
	else if (ft_strchr(MP_SECRETS, obj))
		load_secret_data(scene, x, y, obj);
}

void			parse_map(t_scene *scene)
{
	t_map_data		*md;
	int				x;
	int				y;
	char			obj;

	md = &scene->map_data;
	y = 0;
	while (y < md->height)
	{
		x = 0;
		while (x < md->width)
		{
			obj = (md->map)[y][x];
			if (!ft_strchr(MP_DEFINED_OBJECTS, obj))
				exit_failure("Invalid map object at position [%s][%s]: %c\n", \
				ft_itoa(x, 10), ft_itoa(y, 10), obj);
			process_map_object(scene, x, y, obj);
			++x;
		}
		++y;
	}
	if ((scene->player_data).pos_x == -1)
		exit_failure("Map is missing player's start position\n");
}
