/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_key_states.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:23:26 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/10 20:02:46 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keycodes.h"
#include "process_key_states.h"

static void		move_forward(t_scene *scene, t_player_data *pd)
{
	if (!object_collision(scene, pd->pos_x + pd->dir_x * pd->move_speed, \
		pd->pos_y))
		pd->pos_x += pd->dir_x * pd->move_speed;
	if (!object_collision(scene, pd->pos_x, pd->pos_y + pd->dir_y * \
		pd->move_speed))
		pd->pos_y += pd->dir_y * pd->move_speed;
}

static void		move_backward(t_scene *scene, t_player_data *pd)
{
	if (!object_collision(scene, pd->pos_x - pd->dir_x * pd->move_speed, \
		pd->pos_y))
		pd->pos_x -= pd->dir_x * pd->move_speed;
	if (!object_collision(scene, pd->pos_x, pd->pos_y - pd->dir_y * \
		pd->move_speed))
		pd->pos_y -= pd->dir_y * pd->move_speed;
}

static void		move_left(t_scene *scene, t_player_data *pd)
{
	if (!object_collision(scene, pd->pos_x - pd->plane_x * pd->move_speed, \
		pd->pos_y))
		pd->pos_x -= pd->plane_x * pd->move_speed;
	if (!object_collision(scene, pd->pos_x, pd->pos_y - pd->plane_y * \
		pd->move_speed))
		pd->pos_y -= pd->plane_y * pd->move_speed;
}

static void		move_right(t_scene *scene, t_player_data *pd)
{
	if (!object_collision(scene, pd->pos_x + pd->plane_x * pd->move_speed, \
		pd->pos_y))
		pd->pos_x += pd->plane_x * pd->move_speed;
	if (!object_collision(scene, pd->pos_x, pd->pos_y + pd->plane_y * \
		pd->move_speed))
		pd->pos_y += pd->plane_y * pd->move_speed;
}

void			process_key_states(t_scene *scene)
{
	t_key_states		*ks;
	t_player_data	*pd;

	ks = &scene->key_states;
	pd = &scene->player_data;
	set_player_speed(pd, ks, (*scene).mlx_data.frame_time);
	if (ks->kvk_ansi_w == KEY_DOWN)
		move_forward(scene, pd);
	if (ks->kvk_ansi_s == KEY_DOWN)
		move_backward(scene, pd);
	if (ks->kvk_ansi_a == KEY_DOWN)
		move_left(scene, pd);
	if (ks->kvk_ansi_d == KEY_DOWN)
		move_right(scene, pd);
	if (ks->kvk_leftarrow == KEY_DOWN)
		rotate_left(pd, pd->rot_speed);
	if (ks->kvk_rightarrow == KEY_DOWN)
		rotate_right(pd, pd->rot_speed);
	if (ks->kvk_uparrow == KEY_DOWN)
		rotate_up(pd, pd->rot_speed);
	if (ks->kvk_downarrow == KEY_DOWN)
		rotate_down(pd, pd->rot_speed);
}
