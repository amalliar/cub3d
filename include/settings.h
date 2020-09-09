/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:34:18 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/09 12:05:41 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# define GAME_WINDOW_WIDTH		1280
# define GAME_WINDOW_HEIGHT		720
# define HUD_SCALE				GAME_WINDOW_WIDTH / 304.0
# define HUD_WIDTH				GAME_WINDOW_WIDTH
# define HUD_HEIGHT				35 * HUD_SCALE
# define MLX_WINDOW_TITLE		"cub3D"
# define MLX_WINDOW_WIDTH		GAME_WINDOW_WIDTH
# define MLX_WINDOW_HEIGHT		GAME_WINDOW_HEIGHT + HUD_HEIGHT

# define DEFINED_MAP_OBJECTS	OUTER_MAP_OBJECTS INNER_MAP_OBJECTS
# define OUTER_MAP_OBJECTS		" " BLOCKS
# define INNER_MAP_OBJECTS		"0^_<>" OBJECTS
# define BLOCKS					"!ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define OBJECTS			"abcdefghijklmnopqrstuvwxyz123456789\"#$%&'()*+,."
# define NS						"NP"
# define EW						"OQ"
# define DOORS					NS EW
# define COLLIDERS				"!ABCDEFGHIJKLMRSTUVWXYZbcdilmnq\"#$&"
# define COLLISION_RADIUS		0.20

# define PLAYER_FOV				80
# define PLAYER_MOVE_SPEED		6
# define PLAYER_ROT_SPEED		2
# define PLAYER_MOUSE_SENSE		0.025
# define PLAYER_MAX_HEALTH		100
# define PLAYER_MAX_AMMO		99
# define PLAYER_MAX_PICKUP_DIST	0.50
# define PLAYER_MAX_INTERACT_DIST	1.0
# define PLAYER_JUMP_HEIGHT		250
# define GRAVITY				9.807 * 1000

# define NUM_WALL_TEXTURES		52
# define NUM_OBJECT_TEXTURES	47
# define NUM_HUD_TEXTURES		17

#endif
