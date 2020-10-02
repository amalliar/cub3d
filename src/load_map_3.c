/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:29:37 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 19:16:03 by amalliar         ###   ########.fr       */
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
