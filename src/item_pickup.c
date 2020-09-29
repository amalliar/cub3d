/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_pickup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 22:08:48 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 03:22:19 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "item_pickup.h"
#include "snd.h"

void	attempt_ammo_pickup(t_scene *scene, t_sprite *obj)
{
	t_player_data	*pd;

	pd = &scene->player_data;
	if (obj->type == '1' && pd->ammo < PL_MAX_AMMO)
	{
		pd->ammo = (pd->ammo + 8 <= PL_MAX_AMMO) ? \
			pd->ammo + 8 : PL_MAX_AMMO;
		obj->state = TAKEN;
	}
	else if (obj->type == '.' && pd->ammo < PL_MAX_AMMO)
	{
		pd->ammo = (pd->ammo + 4 <= PL_MAX_AMMO) ? \
			pd->ammo + 4 : PL_MAX_AMMO;
		obj->state = TAKEN;
	}
	if (obj->state == TAKEN)
	{
		playSoundFromMemory((scene->sounds)[SND_AMMO], G_SOUNDS_VOLUME);
		(pd->effects).r_item_pickup = clock();
	}
}

void	attempt_gibs_pickup(t_scene *scene, t_sprite *obj)
{
	(void)scene;
	(void)obj;
	return ;
}

void	attempt_health_pickup(t_scene *scene, t_sprite *obj)
{
	t_player_data	*pd;

	pd = &scene->player_data;
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
	(obj->state == TAKEN) ? \
		playSoundFromMemory((scene->sounds)[SND_HEALTH], G_SOUNDS_VOLUME) : 0;
	(obj->state == TAKEN) ? \
		(pd->effects).r_item_pickup = clock() : 0;
}

void	attempt_key_pickup(t_scene *scene, t_sprite *obj)
{
	(void)scene;
	(void)obj;
	return ;
}
