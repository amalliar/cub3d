/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_pickup_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 22:51:42 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/28 01:17:26 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "item_pickup.h"

void		attempt_powerup_pickup(t_player_data *pd, t_sprite *obj)
{
	if (obj->type == '8')
	{
		pd->health = 100;
		pd->lives += 1;
		pd->ammo = (pd->ammo + 25 <= PLAYER_MAX_AMMO) ? \
			pd->ammo + 25 : PLAYER_MAX_AMMO;
		obj->state = TAKEN;
	}
}

void		attempt_treasure_pickup(t_player_data *pd, t_sprite *obj)
{
	if (obj->type == '4')
	{
		pd->score += 100;
		obj->state = TAKEN;
	}
	else if (obj->type == '5')
	{
		pd->score += 500;
		obj->state = TAKEN;
	}
	else if (obj->type == '6')
	{
		pd->score += 1000;
		obj->state = TAKEN;
	}
	else if (obj->type == '7')
	{
		pd->score += 5000;
		obj->state = TAKEN;
	}
}

void		attempt_weapon_pickup(t_player_data *pd, t_sprite *obj)
{
	(void)pd;
	(void)obj;
	return ;
}
