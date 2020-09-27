/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:37:33 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 06:01:18 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_SCENE_H
# define LOAD_SCENE_H

# include "cub3d.h"
# include "ft_list.h"

char		**gen_map(t_list *lst, int *width, int *height);
void		init_player_weapons(t_player_data *pd, t_mlx_image *hud);
void		load_textures(t_scene *scene);
void		parse_map(t_scene *scene);

#endif
