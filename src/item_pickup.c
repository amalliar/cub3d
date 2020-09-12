/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_pickup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 22:08:48 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 18:58:46 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "item_pickup.h"

void	attempt_ammo_pickup(t_player_data *pd, t_sprite *obj)
{
	if (obj->type == '1' && pd->ammo < PL_MAX_AMMO)
	{
		pd->ammo = (pd->ammo + 8 <= PL_MAX_AMMO) ? \
			pd->ammo + 8 : PL_MAX_AMMO;
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
	if (obj->type == 'g' && pd->health < PL_MAX_HEALTH)
	{
		pd->health = (pd->health + 4 <= PL_MAX_HEALTH) ? \
			pd->health + 4 : PL_MAX_HEALTH;
		obj->state = TAKEN;
	}
	else if (obj->type == 'y' && pd->health < PL_MAX_HEALTH)
	{
		pd->health = (pd->health + 10 <= PL_MAX_HEALTH) ? \
			pd->health + 10 : PL_MAX_HEALTH;
		obj->state = TAKEN;
	}
	else if (obj->type == 'z' && pd->health < PL_MAX_HEALTH)
	{
		pd->health = (pd->health + 25 <= PL_MAX_HEALTH) ? \
			pd->health + 25 : PL_MAX_HEALTH;
		obj->state = TAKEN;
	}
}

void	attempt_key_pickup(t_player_data *pd, t_sprite *obj)
{
	(void)pd;
	(void)obj;
	return ;
}
