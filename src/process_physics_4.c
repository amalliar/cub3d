/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_physics_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 08:35:07 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/27 08:57:00 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_physics.h"

static bool		check_return_condition(t_scene *scene, t_weapon *wpn, \
					clock_t r_timer)
{
	if (wpn->state == EMPTY && \
		(double)(clock() - r_timer) / CLOCKS_PER_SEC >= wpn->min_frame_time)
	{
		playSoundFromMemory((scene->sounds)[SND_EMPTYCLIP], G_SOUNDS_VOLUME);
		wpn->state = IDLE;
		return (true);
	}
	if ((wpn->state == IDLE && wpn->frame == 0) || \
		(double)(clock() - r_timer) / CLOCKS_PER_SEC < wpn->min_frame_time)
		return (true);
	return (false);
}

static void		int_process_weapon_state(t_scene *scene, t_weapon *wpn, \
					t_player_data *pd)
{
	if (wpn->type == HITSCAN && pd->ammo > 0)
	{
		if (wpn->frame == 2)
			playSoundFromMemory((scene->sounds)[wpn->id], G_SOUNDS_VOLUME);
		if ((wpn->frame == 2) || (wpn->frame == 3 && wpn->id == 3))
			player_attack(scene);
		pd->ammo -= ((wpn->frame == 2) || (wpn->frame == 3 && wpn->id == 3));
		if (pd->ammo <= 0)
		{
			pd->ammo = 0;
			wpn->state = (wpn->firing_mode == SEMI_AUTO) ? IDLE : EMPTY;
		}
	}
	else if (wpn->frame == 0)
		playSoundFromMemory((scene->sounds)[wpn->id], G_SOUNDS_VOLUME);
	else if (wpn->frame == 2)
		player_attack(scene);
	if (wpn->firing_mode == FULL_AUTO && wpn->state == FIRING && \
		(wpn->frame == 2 || wpn->frame == 3))
		wpn->frame = (wpn->frame == 2) ? 3 : 2;
	else
		wpn->frame = (wpn->frame + 1) % 5;
	if (wpn->frame == 0)
		wpn->state = IDLE;
}

void			process_weapon_state(t_scene *scene)
{
	static clock_t		r_timer = 0;
	t_player_data		*pd;
	t_weapon			*wpn;

	pd = &scene->player_data;
	wpn = pd->active_weapon;
	if (check_return_condition(scene, wpn, r_timer))
		return ;
	int_process_weapon_state(scene, wpn, pd);
	r_timer = clock();
}
