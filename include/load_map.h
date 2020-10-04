/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 20:58:24 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/04 18:17:28 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_MAP_H
# define LOAD_MAP_H

# include "cub3d.h"
# include "ft_ctype.h"
# include "ft_list.h"
# include "ft_stdio.h"
# include "ft_stdlib.h"
# include "ft_string.h"
# include "item_pickup.h"

int			get_cur_line_length(char *line);
void		build_map_lst(int fd, t_list **lst);
void		check_neighbours(t_map_data *md, int mx, int my);
void		gen_map(t_list *lst, t_map_data *md);
void		gen_map_line(char *dest, char *src, int max_len);
void		get_map_size(t_list *lst, int *width, int *height);
void		init_player_stats(t_player_data *pd);
void		init_player_weapons(t_player_data *pd, t_mlx_image *hud);
void		load_door_data(t_scene *scene, int x, int y, char obj);
void		load_enemie_data(t_scene *scene, int x, int y, char obj);
void		load_object_data(t_scene *scene, int x, int y, char obj);
void		load_player_data(t_player_data *player_data, int x, int y, \
				char obj);
void		load_secret_data(t_scene *scene, int x, int y, char obj);
void		parse_map(t_scene *scene, t_map_data *md);
void		process_map_object(t_scene *scene, int x, int y, char obj);

#endif
