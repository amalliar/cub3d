/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 16:19:16 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/23 00:52:41 by amalliar         ###   ########.fr       */
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
	"./res/sounds/07_pickup.wav",
	"./res/sounds/08_wallhit.wav",
	"./res/sounds/09_bonus1.wav",
	"./res/sounds/10_bonus2.wav",
	"./res/sounds/11_bonus3.wav",
	"./res/sounds/12_bonus4.wav",
	"./res/sounds/13_bns1up.wav",
	"./res/sounds/14_gunup.wav",
	"./res/sounds/15_jump.wav",
	"./res/sounds/16_wpnswitch.wav",
	"./res/sounds/17_secret.wav",
	"./res/sounds/18_emptyclip.wav",
	"./res/sounds/19_death.wav",
	"./res/sounds/20_pain.wav",
	"./res/sounds/21_halt.wav"
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
	SND_PICKUP,
	SND_WALLHIT,
	SND_BONUS1,
	SND_BONUS2,
	SND_BONUS3,
	SND_BONUS4,
	SND_BNS1UP,
	SND_GUNUP,
	SND_JUMP,
	SND_WPNSWITCH,
	SND_SECRET,
	SND_EMPTYCLIP,
	SND_DEATH,
	SND_PAIN,
	SND_HALT
};

#endif
