/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 22:31:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/03 21:03:32 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_scene.h"

void	load_scene(t_scene *scene, char *path)
{
	load_audio(scene);
	load_textures(scene);
	load_map(scene, path);
	playMusicFromMemory((scene->music)[0], G_MUSIC_VOLUME);
}
