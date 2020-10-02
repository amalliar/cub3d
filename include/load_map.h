/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:20:35 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 19:15:36 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_MAP_H
# define LOAD_MAP_H
# define MP_INNER_OBJECTS		"02NSEW"

# include "cub3d.h"
# include "ft_ctype.h"
# include "ft_list.h"
# include "ft_stdio.h"
# include "ft_stdlib.h"
# include "ft_string.h"

char		**gen_map(t_list *lst, int *width, int *height);
size_t		get_cur_line_length(char *line);
void		build_map_lst(int fd, char **line, t_list **lst);
void		check_neighbours(t_map_data *map_data, int mx, int my);
void		gen_map_line(char *dest, char *src, int num);
void		get_map_size(t_list *lst, int *width, int *height);
void		load_map(t_scene *scene, int fd);
void		load_player_data(t_player_data *player_data, int x, int y, \
				char obj);
void		parse_map(t_scene *scene);
void		process_map_object(t_scene *scene, int x, int y, char obj);
void		skip_empty_lines(int fd, char **line);

#endif
