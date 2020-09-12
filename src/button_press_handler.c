/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_press_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 15:47:06 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 15:59:17 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "events.h"

static void		fire_weapon(t_player_data *pd)
{
	t_weapon		*wpn;

	wpn = pd->active_weapon;
	if (pd->ammo > 0 || wpn->type == MELEE)
		wpn->state = FIRING;
}

int				button_press_handler(int button, int x, int y, t_scene *scene)
{
	t_button_states		*bs;
	t_player_data		*pd;

	(void)x;
	(void)y;
	bs = &scene->button_states;
	pd = &scene->player_data;
	if (button == MB_LEFT)
	{
		bs->mb_left = KEY_DOWN;
		fire_weapon(pd);
	}
	return (0);
}
