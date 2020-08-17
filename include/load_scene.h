/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:37:33 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/17 16:07:10 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_SCENE_H
# define LOAD_SCENE_H

# define MANDATORY_PARAMS_COUNT		8
# define PARAMS_LOADED				200

# include "cub3d.h"
# include "ft_list.h"

void		load_scene(t_scene *scene, char *path);
int			parse_params(t_scene *scene, char *line);
int			word_count(char **words);
void		set_color(t_colors *colors, char **words);
void		free_split_tab(char **words);
void		parse_map(t_scene *scene);
void		check_neighbours(t_map_data *map_data, int mx, int my);
char		**gen_map(t_list *lst, int *width, int *height);

#endif
