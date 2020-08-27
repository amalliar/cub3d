/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_pickup.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 22:05:51 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/28 01:15:51 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEM_PICKUP_H
# define ITEM_PICKUP_H

# define AMMO_PICKUPS		"1"
# define GIBS_PICKUPS		""
# define HEALTH_PICKUPS		"gyz"
# define KEY_PICKUPS		""
# define POWERUP_PICKUPS	"8"
# define TREASURE_PICKUPS	"4567"
# define WEAPON_PICKUPS		""
# define PU1 AMMO_PICKUPS GIBS_PICKUPS HEALTH_PICKUPS KEY_PICKUPS
# define PU2 POWERUP_PICKUPS TREASURE_PICKUPS WEAPON_PICKUPS
# define PICKUPS PU1 PU2

# include "cub3d.h"

enum	e_object_states
{
	PLACED,
	TAKEN,
	NOT_A_PICKUP
};

void	attempt_ammo_pickup(t_player_data *pd, t_sprite *obj);
void	attempt_gibs_pickup(t_player_data *pd, t_sprite *obj);
void	attempt_health_pickup(t_player_data *pd, t_sprite *obj);
void	attempt_key_pickup(t_player_data *pd, t_sprite *obj);
void	attempt_powerup_pickup(t_player_data *pd, t_sprite *obj);
void	attempt_treasure_pickup(t_player_data *pd, t_sprite *obj);
void	attempt_weapon_pickup(t_player_data *pd, t_sprite *obj);

#endif
