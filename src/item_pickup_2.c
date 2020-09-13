/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_pickup_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 22:51:42 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/13 19:43:16 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "item_pickup.h"
#include "key_press_handler.h"
#include "snd.h"

void		attempt_powerup_pickup(t_scene *scene, t_sprite *obj)
{
	t_player_data	*pd;

	pd = &scene->player_data;
	if (obj->type == '8')
	{
		playSoundFromMemory((scene->sounds)[SND_PICKUP], G_SOUNDS_VOLUME);
		pd->health = 100;
		if (pd->lives < 9)
			pd->lives += 1;
		pd->ammo = (pd->ammo + 25 <= PL_MAX_AMMO) ? \
			pd->ammo + 25 : PL_MAX_AMMO;
		obj->state = TAKEN;
	}
}

void		attempt_treasur_pickup(t_scene *scene, t_sprite *obj)
{
	t_player_data	*pd;

	pd = &scene->player_data;
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
	if (obj->state == TAKEN)
		playSoundFromMemory((scene->sounds)[SND_PICKUP], G_SOUNDS_VOLUME);
}

void		attempt_weapon_pickup(t_scene *scene, t_sprite *obj)
{
	t_player_data	*pd;
	int				id;

	pd = &scene->player_data;
	id = obj->type - '0';
	if (!(pd->weapons)[id].unlocked || pd->ammo < PL_MAX_AMMO)
	{
		pd->ammo = (pd->ammo + 6 <= PL_MAX_AMMO) ? \
			pd->ammo + 6 : PL_MAX_AMMO;
		if (!(pd->weapons)[id].unlocked)
		{
			(pd->weapons)[id].unlocked = true;
			playSoundFromMemory((scene->sounds)[SND_PICKUP], G_SOUNDS_VOLUME);
			switch_weapon(pd, id);
			if (id == 3)
				(pd->effects).r_bj_evil_grin = clock();
		}
		else
			playSoundFromMemory((scene->sounds)[SND_AMMO], G_SOUNDS_VOLUME);
		obj->state = TAKEN;
	}
}
