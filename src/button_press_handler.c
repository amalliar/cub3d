/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_press_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 15:47:06 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 03:04:53 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "events.h"
#include "snd.h"

static void		fire_weapon(t_scene *scene)
{
	t_player_data	*pd;
	t_weapon		*wpn;

	pd = &scene->player_data;
	wpn = pd->active_weapon;
	if (pd->ammo > 0 || wpn->type == MELEE)
		wpn->state = FIRING;
	else
		playSoundFromMemory((scene->sounds)[SND_EMPTYCLIP], G_SOUNDS_VOLUME);
}

int				button_press_handler(int button, int x, int y, t_scene *scene)
{
	t_button_states		*bs;
	t_player_data		*pd;

	(void)x;
	(void)y;
	if (scene->game_state != GS_NORMAL)
		return (0);
	bs = &scene->button_states;
	pd = &scene->player_data;
	if (button == MB_LEFT)
	{
		bs->mb_left = KEY_DOWN;
		fire_weapon(scene);
	}
	return (0);
}
