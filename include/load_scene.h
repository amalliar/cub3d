/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:37:33 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/14 19:16:43 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_SCENE_H
# define LOAD_SCENE_H
# include "ft_list.h"

int			parse_params(t_scene *scene, char *line);
int			word_count(char **words);
void		set_color(t_colors *colors, char **words);
void		free_split_tab(char **words);
void		parse_map(t_scene *scene);
void		check_neighbours(t_map_data *map_data, int mx, int my);
char		**gen_map(t_list *lst, int *width, int *height);

#endif
