/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:34:18 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/14 21:57:45 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# define G_GAME_WINDOW_WIDTH	1280
# define G_GAME_WINDOW_HEIGHT	720
# define G_HUD_SCALE			G_GAME_WINDOW_WIDTH / 304.0
# define G_HUD_WIDTH			G_GAME_WINDOW_WIDTH
# define G_HUD_HEIGHT			35 * G_HUD_SCALE
# define G_MLX_WINDOW_TITLE		"cub3D"
# define G_MLX_WINDOW_WIDTH		G_GAME_WINDOW_WIDTH
# define G_MLX_WINDOW_HEIGHT	G_GAME_WINDOW_HEIGHT + G_HUD_HEIGHT
# define G_MUSIC_VOLUME			SDL_MIX_MAXVOLUME / 100.0 * 5
# define G_SOUNDS_VOLUME		SDL_MIX_MAXVOLUME / 100.0 * 15

# define SV_GRAVITY				9.807 * 1000

# define MP_OBJECTS			"abcdefghijklmnopqrstuvwxyz123456789\"#$%&'()*+,."
# define MP_BLOCKS				"!ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define MP_OUTER_OBJECTS		" " MP_BLOCKS
# define MP_INNER_OBJECTS		"0^_<>" MP_OBJECTS
# define MP_DEFINED_OBJECTS		MP_OUTER_OBJECTS MP_INNER_OBJECTS
# define NS						"NP"
# define EW						"OQ"
# define MP_DOORS				NS EW
# define MP_NSECRETS			"S"
# define MP_SSECRETS			"T"
# define MP_ESECRETS			""
# define MP_WSECRETS			"RU"
# define MP_SECRETS				MP_NSECRETS MP_SSECRETS MP_ESECRETS MP_WSECRETS
# define MP_COLLIDERS			"!ABCDEFGHIJKLMRSTUVWXYZbcdilmnq\"#$&"
# define MP_COLLISION_RADIUS	0.20

# define PL_CROSSHAIR			0
# define PL_FOV					80
# define PL_JUMP_HEIGHT			250
# define PL_MAX_AMMO			99
# define PL_MAX_HEALTH			100
# define PL_MAX_INTERACT_DIST	0.85
# define PL_MAX_PICKUP_DIST		0.50
# define PL_MOUSE_SENSE			0.025
# define PL_MOVE_SPEED			6
# define PL_ROT_SPEED			2
# define PL_CROSSHAIR_SCALE		1.0
# define PL_WEAPON_SCALE		2.4

# define NUM_CROSSHAIRS			1
# define NUM_FACES_TEXTURES		24
# define NUM_HUD_TEXTURES		17
# define NUM_OBJECT_TEXTURES	47
# define NUM_WALL_TEXTURES		52
# define NUM_WEAPONS			4
# define NUM_WEAPON_FRAMES		5
# define NUM_MUSIC_TRACKS		1
# define NUM_SOUNDS				19

#endif
