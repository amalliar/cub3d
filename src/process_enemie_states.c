/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_enemie_states.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 22:17:54 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/22 02:20:47 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "process_physics.h"
#include "ft_stdlib.h"

static int		get_sprite_angle(t_sprite *sp, t_player_data *pd)
{
	t_fpoint	delta;
	double		mp_angle;
	double		sp_angle;
	double		res_angle;

	delta.x = pd->pos_x - sp->x;
	delta.y = pd->pos_y - sp->y;
	mp_angle = atan2(delta.y, delta.x) * 180 / M_PI;
	sp_angle = atan2(sp->e_data->dir_y, sp->e_data->dir_x) * 180 / M_PI;
	if (mp_angle < 0)
		mp_angle = 360 + mp_angle;
	if (sp_angle < 0)
		sp_angle = 360 + sp_angle;
	res_angle = sp_angle - mp_angle;
	if (res_angle < 0)
		res_angle = 360 + res_angle;
	return ((int)round(res_angle / 45.0) % 8);
}

static void		int_process_enemie_state(t_scene *scene, t_sprite *en)
{
	t_enemie_data	*ed;

	ed = en->e_data;
	if (ed->health <= 0 && ed->is_alive)
	{
		ed->is_alive = false;
		ed->state = &g_grddie0;
	}
	if (ed->state->soundnum > 0 && ed->r_timer == 0)
		playSoundFromMemory((scene->sounds)[ed->state->soundnum], \
			G_SOUNDS_VOLUME);
	else if (ed->r_timer == 0)
		ed->r_timer = clock();
	if (ed->state->s_max_time > 0 && \
	(double)(clock() - ed->r_timer) / CLOCKS_PER_SEC >= ed->state->s_max_time)
	{
		ed->state = ed->state->next;
		ed->r_timer = 0;
	}
	en->tex = (scene->textures).guard + ed->state->shapenum;
	if (ed->state->rotate)
		en->tex += get_sprite_angle(en, &scene->player_data);
	if (ed->state->func != NULL && ed->r_timer == 0)
		ed->state->func(scene, en);
}

void		drop_ammo(t_scene *scene, t_sprite *en)
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
}

void		process_enemie_states(t_scene *scene)
{
	t_sprite_data	*sd;
	int				i;

	sd = &scene->sprite_data;
	i = 0;
	while (i < sd->num_sprites)
	{
		if (ft_strchr(MP_ENEMIES, (scene->sprites)[i].type))
			int_process_enemie_state(scene, scene->sprites + i);
		++i;
	}
}
