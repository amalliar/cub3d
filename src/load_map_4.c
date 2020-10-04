/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:20:39 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/04 17:50:19 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_map.h"

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

void			load_player_data(t_player_data *player_data, int x, int y, \
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

void			load_object_data(t_scene *scene, int x, int y, char obj)
{
	t_sprite		*this_sprite;
	t_sprite_data	*sd;

	sd = &scene->sprite_data;
	if (!(scene->sprites = ft_realloc(scene->sprites, \
		sd->num_sprites * sizeof(t_sprite), \
		(sd->num_sprites + 1) * sizeof(t_sprite))))
		exit_failure("%s\n", strerror(errno));
	this_sprite = scene->sprites + sd->num_sprites;
	this_sprite->x = x + 0.5;
	this_sprite->y = y + 0.5;
	this_sprite->tex = (scene->textures).objects + \
		(ft_strchr(MP_OBJECTS, obj) - MP_OBJECTS);
	this_sprite->state = \
		(ft_strchr(MP_PICKUPS, obj)) ? PLACED : NOT_A_PICKUP;
	this_sprite->type = obj;
	sd->num_sprites += 1;
}
