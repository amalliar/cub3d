/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:37:33 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 14:18:48 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_SCENE_H
# define LOAD_SCENE_H

# include "cub3d.h"
# include "ft_list.h"

char		**gen_map(t_list *lst, int *width, int *height);
void		check_neighbours(t_map_data *map_data, int mx, int my);
void		init_player_weapons(t_player_data *pd, t_mlx_image *hud);
void		load_scene(t_scene *scene, char *path);
void		load_textures(t_scene *scene);
void		parse_map(t_scene *scene);

#endif
