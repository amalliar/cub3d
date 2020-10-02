/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:37:33 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 18:34:06 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_SCENE_H
# define LOAD_SCENE_H

# include "cub3d.h"

void	load_scene(t_scene *scene, char *path);
void	load_params(t_scene *scene, int fd);
void	load_map(t_scene *scene, int fd);

#endif
