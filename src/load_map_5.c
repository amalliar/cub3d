/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:22:25 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/04 17:23:11 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_map.h"

static void		set_enemie_dir(t_sprite *sp)
{
	if (ft_strchr("|", sp->type))
	{
		sp->e_data->dir_x = 0;
		sp->e_data->dir_y = -1;
	}
	else if (ft_strchr("~", sp->type))
	{
		sp->e_data->dir_x = 0;
		sp->e_data->dir_y = 1;
	}
	else if (ft_strchr("{", sp->type))
	{
		sp->e_data->dir_x = -1;
		sp->e_data->dir_y = 0;
	}
	else if (ft_strchr("}", sp->type))
	{
		sp->e_data->dir_x = 1;
		sp->e_data->dir_y = 0;
	}
}

void			load_enemie_data(t_scene *scene, int x, int y, char obj)
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
	this_sprite->type = obj;
	this_sprite->tex = (scene->textures).guard;
	if (!(this_sprite->e_data = malloc(sizeof(t_enemie_data))))
		exit_failure("%s\n", strerror(errno));
	set_enemie_dir(this_sprite);
	this_sprite->e_data->state = (SV_NO_WAR) ? &g_grdidle : &g_grdstand;
	this_sprite->e_data->is_alive = true;
	this_sprite->e_data->is_tracking_player = false;
	this_sprite->e_data->r_timer = 0;
	this_sprite->e_data->health = 32;
	sd->num_sprites += 1;
}

void			load_door_data(t_scene *scene, int x, int y, char obj)
{
	t_door		*this_door;

	if (!(scene->doors = ft_realloc(scene->doors, \
		scene->num_doors * sizeof(t_door), \
		(scene->num_doors + 1) * sizeof(t_door))))
		exit_failure("%s\n", strerror(errno));
	this_door = scene->doors + scene->num_doors;
	this_door->x = x;
	this_door->y = y;
	this_door->state = CLOSED;
	this_door->s_timer = 1.0;
	this_door->type = obj;
	scene->num_doors += 1;
}

void			load_secret_data(t_scene *scene, int x, int y, char obj)
{
	t_secret	*this_secret;

	if (!(scene->secrets = ft_realloc(scene->secrets, \
		scene->num_secrets * sizeof(t_secret), \
		(scene->num_secrets + 1) * sizeof(t_secret))))
		exit_failure("%s\n", strerror(errno));
	this_secret = scene->secrets + scene->num_secrets;
	this_secret->x = x;
	this_secret->y = y;
	this_secret->state = INACTIVE;
	this_secret->s_timer = 0.0;
	this_secret->type = obj;
	scene->num_secrets += 1;
}
