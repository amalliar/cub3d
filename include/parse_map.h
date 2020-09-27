/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 05:46:31 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 06:03:00 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP_H
# define PARSE_MAP_H

# include "ft_ctype.h"
# include "ft_stdlib.h"
# include "ft_string.h"
# include "item_pickup.h"

void	check_neighbours(t_map_data *map_data, int mx, int my);
void	load_object_data(t_scene *scene, int x, int y, char obj);
void	load_enemie_data(t_scene *scene, int x, int y, char obj);
void	load_door_data(t_scene *scene, int x, int y, char obj);
void	load_secret_data(t_scene *scene, int x, int y, char obj);

#endif
