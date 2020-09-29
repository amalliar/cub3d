/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_enemie_states_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 00:28:11 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 08:50:50 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_enemie_states.h"

void		drop_ammo_and_score_points(t_scene *scene, t_sprite *en)
{
	t_sprite		*this_sprite;
	t_sprite_data	*sd;

	sd = &scene->sprite_data;
	if (!(scene->sprites = ft_realloc(scene->sprites, \
		sd->num_sprites * sizeof(t_sprite), \
		(sd->num_sprites + 1) * sizeof(t_sprite))))
		exit_failure("%s\n", strerror(errno));
	this_sprite = scene->sprites + sd->num_sprites;
	this_sprite->x = en->x - 0.1;
	this_sprite->y = en->y;
	this_sprite->tex = (scene->textures).objects + 26;
	this_sprite->state = PLACED;
	this_sprite->type = '.';
	sd->num_sprites += 1;
	(scene->player_data).score += 100;
}

void		alert_neighbours(t_scene *scene, t_sprite *en)
{
	t_sprite	*sprites;
	int			i;

	sprites = scene->sprites;
	i = 0;
	while (i < (scene->sprite_data).num_sprites)
	{
		if (ft_strchr(MP_ENEMIES, sprites[i].type) && \
			sqrt(pow(sprites[i].x - en->x, 2) + pow(sprites[i].y - en->y, 2)) \
			<= EN_INTERACT_DIST)
			start_player_tracking(scene, sprites + i);
		++i;
	}
}

void		start_player_tracking(t_scene *scene, t_sprite *en)
{
	if (!en->e_data->is_tracking_player)
	{
		en->e_data->is_tracking_player = true;
		alert_neighbours(scene, en);
	}
}

void		adjust_view_dir(t_scene *scene, t_sprite *en)
{
	t_player_data	*pd;

	pd = &scene->player_data;
	en->e_data->dir_x = (pd->pos_x - en->x) / en->dist;
	en->e_data->dir_y = (pd->pos_y - en->y) / en->dist;
}
