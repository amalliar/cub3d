/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_key_states_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:38:17 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/30 11:01:34 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_key_states.h"

/*
** Player moves independent of current frame rate.
*/

void		set_player_speed(t_player_data *pd, t_key_states *ks, \
				double frame_time)
{
	double		speed_modifier;

	speed_modifier = 1.0;
	if ((ks->xk_w == KEY_DOWN || ks->xk_s == KEY_DOWN) && \
		(ks->xk_a == KEY_DOWN || ks->xk_d == KEY_DOWN))
		speed_modifier = 0.50;
	if (pd->pos_z < 0)
		speed_modifier /= 2.0;
	pd->move_speed = frame_time * PL_MOVE_SPEED * speed_modifier;
	pd->rot_speed = frame_time * PL_ROT_SPEED;
}

void		rotate_left(t_player_data *pd, double rot_speed)
{
	pd->old_dir_x = pd->dir_x;
	pd->dir_x = pd->dir_x * cos(-rot_speed) - pd->dir_y * \
		sin(-rot_speed);
	pd->dir_y = pd->old_dir_x * sin(-rot_speed) + pd->dir_y * \
		cos(-rot_speed);
	pd->old_plane_x = pd->plane_x;
	pd->plane_x = pd->plane_x * cos(-rot_speed) - pd->plane_y * \
		sin(-rot_speed);
	pd->plane_y = pd->old_plane_x * sin(-rot_speed) + pd->plane_y * \
		cos(-rot_speed);
}

void		rotate_right(t_player_data *pd, double rot_speed)
{
	pd->old_dir_x = pd->dir_x;
	pd->dir_x = pd->dir_x * cos(rot_speed) - pd->dir_y * \
		sin(rot_speed);
	pd->dir_y = pd->old_dir_x * sin(rot_speed) + pd->dir_y * \
		cos(rot_speed);
	pd->old_plane_x = pd->plane_x;
	pd->plane_x = pd->plane_x * cos(rot_speed) - pd->plane_y * \
		sin(rot_speed);
	pd->plane_y = pd->old_plane_x * sin(rot_speed) + pd->plane_y * \
		cos(rot_speed);
}

void		rotate_up(t_player_data *pd, double rot_speed)
{
	pd->pitch += 400 * rot_speed;
	if (pd->pitch > 600)
		pd->pitch = 600;
}

void		rotate_down(t_player_data *pd, double rot_speed)
{
	pd->pitch -= 400 * rot_speed;
	if (pd->pitch < -600)
		pd->pitch = -600;
}
