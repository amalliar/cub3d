/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:18:19 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/14 19:47:11 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCKS_H
# define BLOCKS_H
# include "textures.h"

typedef struct		s_block
{
	int				id_tex_n;
	int				id_tex_s;
	int				id_tex_e;
	int				id_tex_w;
}					t_block;

static t_block		g_blocks[] =
{
	{
		DEV_N,
		DEV_S,
		DEV_E,
		DEV_W
	},
	{
		BLUE_TILE_WALL,
		BLUE_TILE_WALL,
		BLUE_TILE_WALL_DARK,
		BLUE_TILE_WALL_DARK
	},
	{
		BLUE_TILE_WALL_2,
		BLUE_TILE_WALL_2,
		BLUE_TILE_WALL_2_DARK,
		BLUE_TILE_WALL_2_DARK
	},
	{
		BLUE_TILE_DOOR,
		BLUE_TILE_DOOR,
		BLUE_TILE_DOOR_DARK,
		BLUE_TILE_DOOR_DARK
	},
	{
		BLUE_TILE_SKEL,
		BLUE_TILE_SKEL,
		BLUE_TILE_SKEL_DARK,
		BLUE_TILE_SKEL_DARK
	},
	{
		GREY_STONE_WALL,
		GREY_STONE_WALL,
		GREY_STONE_WALL_DARK,
		GREY_STONE_WALL_DARK,
	},
	{
		GREY_STONE_WALL_2,
		GREY_STONE_WALL_2,
		GREY_STONE_WALL_2_DARK,
		GREY_STONE_WALL_2_DARK,
	},
	{
		GREY_STONE_ARCH,
		GREY_STONE_ARCH,
		GREY_STONE_ARCH_DARK,
		GREY_STONE_ARCH_DARK
	},
	{
		GREY_STONE_HITLER_PICTURE,
		GREY_STONE_HITLER_PICTURE,
		GREY_STONE_HITLER_PICTURE_DARK,
		GREY_STONE_HITLER_PICTURE_DARK,
	},
	{
		GREY_STONE_BANNER,
		GREY_STONE_BANNER,
		GREY_STONE_BANNER_DARK,
		GREY_STONE_BANNER_DARK,
	},
	{
		WOODEN_WALL,
		WOODEN_WALL,
		WOODEN_WALL_DARK,
		WOODEN_WALL_DARK
	},
	{
		WOODEN_EAGLE_PICTURE,
		WOODEN_EAGLE_PICTURE,
		WOODEN_EAGLE_PICTURE_DARK,
		WOODEN_EAGLE_PICTURE_DARK
	},
	{
		WOODEN_HITLER_PICTURE,
		WOODEN_HITLER_PICTURE,
		WOODEN_HITLER_PICTURE_DARK,
		WOODEN_HITLER_PICTURE_DARK
	},
	{
		ELEVATOR_DOWN_FRONT,
		ELEVATOR_DOWN_FRONT,
		ELEVATOR_DOWN_SIDE,
		ELEVATOR_DOWN_SIDE,
	},
	{
		CYAN_METAL_DOOR,
		CYAN_METAL_DOOR,
		CYAN_METAL_DOOR_FRAME_DARK,
		CYAN_METAL_DOOR_FRAME_DARK
	},
	{
		CYAN_METAL_DOOR_FRAME,
		CYAN_METAL_DOOR_FRAME,
		CYAN_METAL_DOOR_DARK,
		CYAN_METAL_DOOR_DARK
	},
	{
		ELEVATOR_DOOR,
		ELEVATOR_DOOR,
		CYAN_METAL_DOOR_FRAME_DARK,
		CYAN_METAL_DOOR_FRAME_DARK
	},
	{
		CYAN_METAL_DOOR_FRAME,
		CYAN_METAL_DOOR_FRAME,
		ELEVATOR_DOOR_DARK,
		ELEVATOR_DOOR_DARK
	},
	{
		WOODEN_EAGLE_PICTURE,
		WOODEN_EAGLE_PICTURE,
		WOODEN_EAGLE_PICTURE_DARK,
		WOODEN_EAGLE_PICTURE_DARK
	},
	{
		GREY_STONE_HITLER_PICTURE,
		GREY_STONE_HITLER_PICTURE,
		GREY_STONE_HITLER_PICTURE_DARK,
		GREY_STONE_HITLER_PICTURE_DARK,
	},
	{
		GREY_STONE_WALL,
		GREY_STONE_WALL,
		GREY_STONE_WALL_DARK,
		GREY_STONE_WALL_DARK,
	},
	{
		GREY_STONE_WALL,
		GREY_STONE_WALL,
		GREY_STONE_WALL_DARK,
		GREY_STONE_WALL_DARK,
	}
};

#endif
