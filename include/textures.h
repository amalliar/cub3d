/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:41:39 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/22 20:45:17 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# include "settings.h"

static char		g_wall_texture_paths[NUM_WALL_TEXTURES][128] =
{
	"./res/textures/walls/00_dev_n.xpm",
	"./res/textures/walls/01_dev_s.xpm",
	"./res/textures/walls/02_dev_e.xpm",
	"./res/textures/walls/03_dev_w.xpm",
	"./res/textures/walls/04_grey_stone_wall.xpm",
	"./res/textures/walls/05_grey_stone_wall_dark.xpm",
	"./res/textures/walls/06_grey_stone_wall_2.xpm",
	"./res/textures/walls/07_grey_stone_wall_2_dark.xpm",
	"./res/textures/walls/08_grey_stone_banner.xpm",
	"./res/textures/walls/09_grey_stone_banner_dark.xpm",
	"./res/textures/walls/10_grey_stone_hitler_picture.xpm",
	"./res/textures/walls/11_grey_stone_hitler_picture_dark.xpm",
	"./res/textures/walls/12_blue_tile_door.xpm",
	"./res/textures/walls/13_blue_tile_door_dark.xpm",
	"./res/textures/walls/14_grey_stone_arch.xpm",
	"./res/textures/walls/15_grey_stone_arch_dark.xpm",
	"./res/textures/walls/16_blue_tile_skel.xpm",
	"./res/textures/walls/17_blue_tile_skel_dark.xpm",
	"./res/textures/walls/18_blue_tile_wall.xpm",
	"./res/textures/walls/19_blue_tile_wall_dark.xpm",
	"./res/textures/walls/20_blue_tile_wall_2.xpm",
	"./res/textures/walls/21_blue_tile_wall_2_dark.xpm",
	"./res/textures/walls/22_wooden_eagle_picture.xpm",
	"./res/textures/walls/23_wooden_eagle_picture_dark.xpm",
	"./res/textures/walls/24_wooden_hitler_picture.xpm",
	"./res/textures/walls/25_wooden_hitler_picture_dark.xpm",
	"./res/textures/walls/26_wooden_wall.xpm",
	"./res/textures/walls/27_wooden_wall_dark.xpm",
	"./res/textures/walls/28_grey_metal_door.xpm",
	"./res/textures/walls/29_grey_metal_door_dark.xpm",
	"./res/textures/walls/30_cyan_metal_verboteh_poster.xpm",
	"./res/textures/walls/31_cyan_metal_achtung_poster.xpm",
	"./res/textures/walls/32_cyan_metal_wall.xpm",
	"./res/textures/walls/33_cyan_metal_wall_dark.xpm",
	"./res/textures/walls/34_outside.xpm",
	"./res/textures/walls/35_outside_dark.xpm",
	"./res/textures/walls/36_red_brick_wall.xpm",
	"./res/textures/walls/37_red_brick_wall_dark.xpm",
	"./res/textures/walls/38_red_brick_golden_swastika.xpm",
	"./res/textures/walls/39_red_brick_golden_swastika_dark.xpm",
	"./res/textures/walls/40_purple_wall.xpm",
	"./res/textures/walls/41_purple_wall_dark.xpm",
	"./res/textures/walls/42_red_brick_eagle_banner.xpm",
	"./res/textures/walls/43_red_brick_eagle_banner_dark.xpm",
	"./res/textures/walls/44_elevator_down_front.xpm",
	"./res/textures/walls/45_elevator_down_side.xpm"
};

enum			e_texture_ids
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
	ELEVATOR_DOWN_SIDE
};

static char		g_object_texture_paths[NUM_OBJECT_TEXTURES][128] =
{
	"./res/textures/objects/00_water_puddle.xpm",
	"./res/textures/objects/01_green_barrel.xpm",
	"./res/textures/objects/02_table_with_chairs.xpm",
	"./res/textures/objects/03_floor_lamp.xpm",
	"./res/textures/objects/04_golden_chandelier.xpm",
	"./res/textures/objects/05_hanged_man.xpm",
	"./res/textures/objects/06_dog_food.xpm",
	"./res/textures/objects/07_stone_pillar.xpm",
	"./res/textures/objects/08_green_tree.xpm",
	"./res/textures/objects/09_skeleton.xpm",
	"./res/textures/objects/10_sink.xpm",
	"./res/textures/objects/11_potted_plant.xpm",
	"./res/textures/objects/12_blue_urn.xpm",
	"./res/textures/objects/13_bare_table.xpm",
	"./res/textures/objects/14_green_lamp.xpm",
	"./res/textures/objects/15_kitchenware.xpm",
	"./res/textures/objects/16_suit_of_armor.xpm",
	"./res/textures/objects/17_hanging_cage.xpm",
	"./res/textures/objects/18_skeletonin_cage.xpm",
	"./res/textures/objects/19_pile_of_bones.xpm",
	"./res/textures/objects/20_golden_key.xpm",
	"./res/textures/objects/21_iron_key.xpm",
	"./res/textures/objects/22_bed.xpm",
	"./res/textures/objects/23_pot.xpm",
	"./res/textures/objects/24_food.xpm",
	"./res/textures/objects/25_medkit.xpm",
	"./res/textures/objects/26_ammo.xpm",
	"./res/textures/objects/27_machine_gun.xpm",
	"./res/textures/objects/28_chain_gun.xpm",
	"./res/textures/objects/29_golden_cross.xpm",
	"./res/textures/objects/30_golden_chalice.xpm",
	"./res/textures/objects/31_golden_chest.xpm",
	"./res/textures/objects/32_golden_crown.xpm",
	"./res/textures/objects/33_one_up.xpm",
	"./res/textures/objects/34_gibs_skel.xpm",
	"./res/textures/objects/35_wooden_barrel.xpm",
	"./res/textures/objects/36_well_full.xpm",
	"./res/textures/objects/37_well_empty.xpm",
	"./res/textures/objects/38_gibs_blood.xpm",
	"./res/textures/objects/39_flag.xpm",
	"./res/textures/objects/40_shards.xpm",
	"./res/textures/objects/41_shards_2.xpm",
	"./res/textures/objects/42_shards_3.xpm",
	"./res/textures/objects/43_kitchenware_2.xpm",
	"./res/textures/objects/44_stove.xpm",
	"./res/textures/objects/45_spears.xpm",
	"./res/textures/objects/46_vine.xpm"
};

#endif
