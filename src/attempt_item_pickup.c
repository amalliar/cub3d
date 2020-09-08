/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attempt_item_pickup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:27:45 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/08 15:24:46 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "item_pickup.h"
#include "ft_string.h"

void		attempt_item_pickup(t_scene *scene)
{
	t_player_data	*pd;
	int				i;

	pd = &scene->player_data;
	i = (*scene).sprite_data.num_sprites - 1;
	while (i >= 0 && sqrt((scene->sprites)[i].dist) <= PLAYER_MAX_PICKUP_DIST)
	{
		if ((scene->sprites)[i--].state == PLACED)
		{
			if (ft_strchr(AMMO_PICKUPS, (scene->sprites)[i + 1].type))
				attempt_ammo_pickup(pd, scene->sprites + i + 1);
			else if (ft_strchr(GIBS_PICKUPS, (scene->sprites)[i + 1].type))
				attempt_gibs_pickup(pd, scene->sprites + i + 1);
			else if (ft_strchr(HEALTH_PICKUPS, (scene->sprites)[i + 1].type))
				attempt_health_pickup(pd, scene->sprites + i + 1);
			else if (ft_strchr(KEY_PICKUPS, scene->sprites[i + 1].type))
				attempt_key_pickup(pd, scene->sprites + i + 1);
			else if (ft_strchr(POWERUP_PICKUPS, (scene->sprites)[i + 1].type))
				attempt_powerup_pickup(pd, scene->sprites + i + 1);
			else if (ft_strchr(TREASURE_PICKUPS, (scene->sprites)[i + 1].type))
				attempt_treasure_pickup(pd, scene->sprites + i + 1);
			else if (ft_strchr(WEAPON_PICKUPS, (scene->sprites)[i + 1].type))
				attempt_weapon_pickup(pd, scene->sprites + i + 1);
		}
	}
}
