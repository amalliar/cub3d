/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_enemie_states.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 22:17:54 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/24 00:40:38 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_enemie_states.h"

t_estate		g_grdstand = \
{true, spr_grd_stand_0, 0, check_player_presence, NULL, -1, &g_grdstand};

t_estate		g_grdshoot0 = \
{false, spr_grd_shoot_0, 0.5, NULL, start_player_tracking, -1, &g_grdshoot1};
t_estate		g_grdshoot1 = \
{false, spr_grd_shoot_1, 0.5, NULL, NULL, -1, &g_grdshoot2};
t_estate		g_grdshoot2 = \
{false, spr_grd_shoot_2, 0.5, NULL, NULL, SND_PISTOL, &g_grdshoot3};
t_estate		g_grdshoot3 = \
{false, spr_grd_shoot_2, 0.1, NULL, check_player_presence, -1, &g_grdstand};

t_estate		g_grdpain = \
{false, spr_grd_pain_0, 0.5, NULL, NULL, SND_PAIN, &g_grdshoot0};

t_estate		g_grddie0 = \
{false, spr_grd_die_0, 0.1, NULL, NULL, SND_DEATH, &g_grddie1};
t_estate		g_grddie1 = \
{false, spr_grd_die_1, 0.1, NULL, NULL, -1, &g_grddie2};
t_estate		g_grddie2 = \
{false, spr_grd_die_2, 0.1, NULL, NULL, -1, &g_grddie3};
t_estate		g_grddie3 = \
{false, spr_grd_dead, 0, NULL, drop_ammo, -1, &g_grddie3};

static int		get_view_angle(t_sprite *sp, t_player_data *pd)
{
	t_fpoint	delta;
	double		map_angle;
	double		sprite_angle;
	double		view_angle;

	delta.x = pd->pos_x - sp->x;
	delta.y = pd->pos_y - sp->y;
	map_angle = atan2(delta.y, delta.x) * 180 / M_PI;
	sprite_angle = atan2(sp->e_data->dir_y, sp->e_data->dir_x) * 180 / M_PI;
	if (map_angle < 0)
		map_angle = 360 + map_angle;
	if (sprite_angle < 0)
		sprite_angle = 360 + sprite_angle;
	view_angle = sprite_angle - map_angle;
	if (view_angle < 0)
		view_angle = 360 + view_angle;
	return ((int)round(view_angle / 45.0) % 8);
}

static void		int_process_enemie_state(t_scene *scene, int spritenum)
{
	t_sprite		*en;
	t_enemie_data	*ed;
	double			vperc;

	en = scene->sprites + spritenum;
	ed = en->e_data;
	if (ed->r_timer == 0)
	{
		if (ed->state->soundnum > 0)
		{
			vperc = 100.0 - sqrt(en->dist) * 3.5;
			if (vperc < 0)
				vperc = 0;
			playSoundFromMemory((scene->sounds)[ed->state->soundnum], \
				G_SOUNDS_VOLUME * vperc / 100.0);
		}
		if (ed->state->fonce != NULL)
			ed->state->fonce(scene, en);
		ed->r_timer = clock();
	}
	en = scene->sprites + spritenum;
	ed = en->e_data;
	en->tex = (scene->textures).guard + ed->state->shapenum;
	if (ed->state->rotate)
		en->tex += get_view_angle(en, &scene->player_data);
	if (ed->state->s_max_time > 0 && \
	(double)(clock() - ed->r_timer) / CLOCKS_PER_SEC >= ed->state->s_max_time)
	{
		ed->state = ed->state->next;
		ed->r_timer = 0;
	}
	if (ed->state->falways != NULL)
		ed->state->falways(scene, en);
}

void			process_enemie_states(t_scene *scene)
{
	t_sprite_data	*sd;
	int				i;

	sd = &scene->sprite_data;
	i = 0;
	while (i < sd->num_sprites)
	{
		if (ft_strchr(MP_ENEMIES, (scene->sprites)[i].type))
			int_process_enemie_state(scene, i);
		++i;
	}
}
