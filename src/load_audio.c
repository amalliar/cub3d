/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_audio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 16:16:24 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/24 04:24:56 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "settings.h"

char		g_music_paths[NUM_MUSIC_TRACKS][128] =
{
	"./res/music/00_get_them_before_they_get_you.wav"
};

char		g_sounds_paths[NUM_SOUNDS][128] =
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
	"./res/sounds/21_halt.wav",
	"./res/sounds/22_player_pain.wav",
	"./res/sounds/23_player_pain_critical.wav",
	"./res/sounds/24_player_death.wav"
};

void		load_audio(t_scene *scene)
{
	int		i;

	i = 0;
	while (i < NUM_SOUNDS)
	{
		(scene->sounds)[i] = createAudio(g_sounds_paths[i], 0, G_SOUNDS_VOLUME);
		++i;
	}
	i = 0;
	while (i < NUM_MUSIC_TRACKS)
	{
		(scene->music)[i] = createAudio(g_music_paths[i], 1, G_MUSIC_VOLUME);
		++i;
	}
}
