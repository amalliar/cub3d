/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_key_states.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:47:43 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/23 08:51:08 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_KEY_STATES_H
# define PROCESS_KEY_STATES_H
# include "cub3d.h"

int		door_collision(t_scene *scene, double px, double py, double cr);
int		object_collision(t_scene *scene, double px, double py, double cr);
void	rotate_down(t_player_data *pd, double rot_speed);
void	rotate_left(t_player_data *pd, double rot_speed);
void	rotate_right(t_player_data *pd, double rot_speed);
void	rotate_up(t_player_data *pd, double rot_speed);
void	set_player_speed(t_player_data *pd, t_key_states *ks, \
			double frame_time);

#endif
