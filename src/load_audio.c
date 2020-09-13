/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_audio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 16:16:24 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/13 18:55:09 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "snd.h"

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
