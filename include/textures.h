/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:41:39 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/21 23:27:10 by amalliar         ###   ########.fr       */
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
	"./res/textures/walls/08_grey_stone_wall_banner.xpm",
	"./res/textures/walls/09_grey_stone_wall_banner_dark.xpm",
	"./res/textures/walls/10_grey_stone_wall_hitler_picture.xpm",
	"./res/textures/walls/11_grey_stone_wall_hitler_picture_dark.xpm",
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
};

static char		g_object_texture_paths[NUM_OBJECT_TEXTURES][128] =
{
	"./res/textures/objects/lamp.xpm"
};

#endif
