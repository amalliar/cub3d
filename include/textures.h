/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:41:39 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/29 15:53:45 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

enum		e_texture_ids
{
	DEV_N,
	DEV_S,
	DEV_E,
	DEV_W,
	GREY_STONE_WALL,
	GREY_STONE_WALL_DARK,
	GREY_STONE_WALL_2,
	GREY_STONE_WALL_2_DARK,
	GREY_STONE_BANNER,
	GREY_STONE_BANNER_DARK,
	GREY_STONE_HITLER_PICTURE,
	GREY_STONE_HITLER_PICTURE_DARK,
	BLUE_TILE_DOOR,
	BLUE_TILE_DOOR_DARK,
	GREY_STONE_ARCH,
	GREY_STONE_ARCH_DARK,
	BLUE_TILE_SKEL,
	BLUE_TILE_SKEL_DARK,
	BLUE_TILE_WALL,
	BLUE_TILE_WALL_DARK,
	BLUE_TILE_WALL_2,
	BLUE_TILE_WALL_2_DARK,
	WOODEN_EAGLE_PICTURE,
	WOODEN_EAGLE_PICTURE_DARK,
	WOODEN_HITLER_PICTURE,
	WOODEN_HITLER_PICTURE_DARK,
	WOODEN_WALL,
	WOODEN_WALL_DARK,
	GREY_METAL_DOOR,
	GREY_METAL_DOOR_DARK,
	CYAN_METAL_VERBOTEH_POSTER,
	CYAN_METAL_ACHTUNG_POSTER,
	CYAN_METAL_WALL,
	CYAN_METAL_WALL_DARK,
	OUTSIDE,
	OUTSIDE_DARK,
	RED_BRICK_WALL,
	RED_BRICK_WALL_DARK,
	RED_BRICK_GOLDEN_SWASTIKA,
	RED_BRICK_GOLDEN_SWASTIKA_DARK,
	PURPLE_WALL,
	PURPLE_WALL_DARK,
	RED_BRICK_EAGLE_BANNER,
	RED_BRICK_EAGLE_BANNER_DARK,
	ELEVATOR_DOWN_FRONT,
	ELEVATOR_DOWN_SIDE,
	CYAN_METAL_DOOR,
	CYAN_METAL_DOOR_DARK,
	CYAN_METAL_DOOR_FRAME,
	CYAN_METAL_DOOR_FRAME_DARK,
	ELEVATOR_DOOR,
	ELEVATOR_DOOR_DARK,
	CARMACK_AND_ROMERO
};

enum		e_spr_grd_ids
{
	spr_grd_stand_0 = 0,
	spr_grd_pain_0 = 40,
	spr_grd_die_0,
	spr_grd_die_1,
	spr_grd_die_2,
	spr_grd_dead,
	spr_grd_shoot_0,
	spr_grd_shoot_1,
	spr_grd_shoot_2
};

#endif
