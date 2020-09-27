/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_release_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 15:59:46 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 03:04:44 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "events.h"

int		button_release_handler(int button, int x, int y, t_scene *scene)
{
	t_button_states		*bs;
	t_weapon			*wpn;

	(void)x;
	(void)y;
	if (scene->game_state != GS_NORMAL)
		return (0);
	bs = &scene->button_states;
	wpn = (*scene).player_data.active_weapon;
	if (button == MB_LEFT)
	{
		bs->mb_left = KEY_UP;
		wpn->state = IDLE;
	}
	return (0);
}
