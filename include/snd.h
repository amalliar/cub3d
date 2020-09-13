/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 16:19:16 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/13 19:29:54 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SND_H
# define SND_H

# include "settings.h"

static char		g_music_paths[NUM_MUSIC_TRACKS][128] =
{
	"./res/music/00_get_them_before_they_get_you.wav"
};

static char		g_sounds_paths[NUM_SOUNDS][128] =
{
	"./res/sounds/00_knife.wav",
	"./res/sounds/01_pistol.wav",
	"./res/sounds/02_machinegun.wav",
	"./res/sounds/03_chaingun.wav",
	"./res/sounds/04_door.wav",
	"./res/sounds/05_ammo.wav",
	"./res/sounds/06_health.wav",
	"./res/sounds/07_pickup.wav"
};

enum			e_sounds_ids
{
	SND_KNIFE,
	SND_PISTOL,
	SND_MACHINEGUN,
	SND_CHAINGUN,
	SND_DOOR,
	SND_AMMO,
	SND_HEALTH,
	SND_PICKUP
};

#endif
