/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keystates_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:38:17 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/17 21:43:02 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_keystates.h"

void		set_player_speed(t_player_data *pd, t_mlx_data *mlx_data)
{
	pd->move_speed = mlx_data->frame_time * PLAYER_MOVE_SPEED;
	pd->rot_speed = mlx_data->frame_time * PLAYER_ROT_SPEED;
}

void		turn_left(t_player_data *pd)
{
	pd->old_dir_x = pd->dir_x;
	pd->dir_x = pd->dir_x * cos(-pd->rot_speed) - pd->dir_y * \
		sin(-pd->rot_speed);
	pd->dir_y = pd->old_dir_x * sin(-pd->rot_speed) + pd->dir_y * \
		cos(-pd->rot_speed);
	pd->old_plane_x = pd->plane_x;
	pd->plane_x = pd->plane_x * cos(-pd->rot_speed) - pd->plane_y * \
		sin(-pd->rot_speed);
	pd->plane_y = pd->old_plane_x * sin(-pd->rot_speed) + pd->plane_y * \
		cos(-pd->rot_speed);
}

void		turn_right(t_player_data *pd)
{
	pd->old_dir_x = pd->dir_x;
	pd->dir_x = pd->dir_x * cos(pd->rot_speed) - pd->dir_y * \
		sin(pd->rot_speed);
	pd->dir_y = pd->old_dir_x * sin(pd->rot_speed) + pd->dir_y * \
		cos(pd->rot_speed);
	pd->old_plane_x = pd->plane_x;
	pd->plane_x = pd->plane_x * cos(pd->rot_speed) - pd->plane_y * \
		sin(pd->rot_speed);
	pd->plane_y = pd->old_plane_x * sin(pd->rot_speed) + pd->plane_y * \
		cos(pd->rot_speed);
}
