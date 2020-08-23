/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:34:18 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/23 17:15:38 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# define MLX_WINDOW_WIDTH		1280
# define MLX_WINDOW_HEIGHT		720
# define MLX_WINDOW_TITLE		"cub3D"

# define FLOOR_COLOR			0x707070
# define CEILING_COLOR			0x383838

# define DEFINED_MAP_OBJECTS	OUTER_MAP_OBJECTS INNER_MAP_OBJECTS
# define OUTER_MAP_OBJECTS		" " BLOCKS
# define INNER_MAP_OBJECTS		"0^_<>" OBJECTS
# define BLOCKS					"!ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define OBJECTS			"abcdefghijklmnopqrstuvwxyz123456789\"#$%&'()*+,."
# define COLLIDERS				"!ABCDEFGHIJKLMNOPQRSTUVWXYZbcdilmnq\"#$&"
# define COLLISION_R			0.20

# define PLAYER_FOV				80
# define PLAYER_MOVE_SPEED		6
# define PLAYER_ROT_SPEED		2

# define NUM_WALL_TEXTURES		46
# define NUM_OBJECT_TEXTURES	47

#endif
