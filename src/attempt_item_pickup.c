/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attempt_item_pickup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:27:45 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 04:56:20 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "item_pickup.h"
#include "render_scene.h"

void		attempt_item_pickup(t_scene *scene)
{
	int		i;

	i = (scene->sprite_data).num_sprites - 1;
	while (i >= 0 && (scene->sprites)[i].dist <= PL_MAX_PICKUP_DIST)
	{
		if ((scene->sprites)[i].state == PLACED)
		{
			if (ft_strchr(AMMO_PICKUPS, (scene->sprites)[i].type))
				attempt_ammo_pickup(scene, scene->sprites + i);
			else if (ft_strchr(GIBS_PICKUPS, (scene->sprites)[i].type))
				attempt_gibs_pickup(scene, scene->sprites + i);
			else if (ft_strchr(HEALTH_PICKUPS, (scene->sprites)[i].type))
				attempt_health_pickup(scene, scene->sprites + i);
			else if (ft_strchr(KEY_PICKUPS, scene->sprites[i].type))
				attempt_key_pickup(scene, scene->sprites + i);
			else if (ft_strchr(POWERUP_PICKUPS, (scene->sprites)[i].type))
				attempt_powerup_pickup(scene, scene->sprites + i);
			else if (ft_strchr(TREASURE_PICKUPS, (scene->sprites)[i].type))
				attempt_treasur_pickup(scene, scene->sprites + i, \
					&scene->player_data);
			else if (ft_strchr(WEAPON_PICKUPS, (scene->sprites)[i].type))
				attempt_weapon_pickup(scene, scene->sprites + i);
		}
		--i;
	}
}
