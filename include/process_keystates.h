/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keystates.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:47:43 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/04 07:22:56 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_KEYSTATES_H
# define PROCESS_KEYSTATES_H
# include "cub3d.h"

void	set_player_speed(t_player_data *pd, t_keystates *ks, double frame_time);
void	rotate_left(t_player_data *pd, double rot_speed);
void	rotate_right(t_player_data *pd, double rot_speed);
void	rotate_up(t_player_data *pd, double rot_speed);
void	rotate_down(t_player_data *pd, double rot_speed);
int		object_collision(t_map_data *md, double pos_x, double pos_y);

#endif
