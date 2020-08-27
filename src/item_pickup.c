/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_pickup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 22:08:48 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/28 01:17:15 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "item_pickup.h"

void	attempt_ammo_pickup(t_player_data *pd, t_sprite *obj)
{
	if (obj->type == '1' && pd->ammo < PLAYER_MAX_AMMO)
	{
		pd->ammo = (pd->ammo + 8 <= PLAYER_MAX_AMMO) ? \
			pd->ammo + 8 : PLAYER_MAX_AMMO;
		obj->state = TAKEN;
	}
}

void	attempt_gibs_pickup(t_player_data *pd, t_sprite *obj)
{
	(void)pd;
	(void)obj;
	return ;
}

void	attempt_health_pickup(t_player_data *pd, t_sprite *obj)
{
	if (obj->type == 'g' && pd->health < PLAYER_MAX_HEALTH)
	{
		pd->health = (pd->health + 4 <= PLAYER_MAX_HEALTH) ? \
			pd->health + 4 : PLAYER_MAX_HEALTH;
		obj->state = TAKEN;
	}
	else if (obj->type == 'y' && pd->health < PLAYER_MAX_HEALTH)
	{
		pd->health = (pd->health + 10 <= PLAYER_MAX_HEALTH) ? \
			pd->health + 10 : PLAYER_MAX_HEALTH;
		obj->state = TAKEN;
	}
	else if (obj->type == 'z' && pd->health < PLAYER_MAX_HEALTH)
	{
		pd->health = (pd->health + 25 <= PLAYER_MAX_HEALTH) ? \
			pd->health + 25 : PLAYER_MAX_HEALTH;
		obj->state = TAKEN;
	}
}

void	attempt_key_pickup(t_player_data *pd, t_sprite *obj)
{
	(void)pd;
	(void)obj;
	return ;
}
