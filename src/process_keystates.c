/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keystates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:23:26 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/20 14:56:31 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keycodes.h"
#include "process_keystates.h"

static void		move_forward(t_map_data *md, t_player_data *pd)
{
	if (!object_collision(md, pd->pos_x + pd->dir_x * pd->move_speed * \
		pd->speed_mod, pd->pos_y))
		pd->pos_x += pd->dir_x * pd->move_speed * pd->speed_mod;
	if (!object_collision(md, pd->pos_x, pd->pos_y + pd->dir_y * \
		pd->move_speed * pd->speed_mod))
		pd->pos_y += pd->dir_y * pd->move_speed * pd->speed_mod;
}

static void		move_backward(t_map_data *md, t_player_data *pd)
{
	if (!object_collision(md, pd->pos_x - pd->dir_x * pd->move_speed * \
		pd->speed_mod, pd->pos_y))
		pd->pos_x -= pd->dir_x * pd->move_speed * pd->speed_mod;
	if (!object_collision(md, pd->pos_x, pd->pos_y - pd->dir_y * \
		pd->move_speed * pd->speed_mod))
		pd->pos_y -= pd->dir_y * pd->move_speed * pd->speed_mod;
}

static void		move_left(t_map_data *md, t_player_data *pd)
{
	if (!object_collision(md, pd->pos_x + pd->dir_y * pd->move_speed * \
		pd->speed_mod, pd->pos_y))
		pd->pos_x += pd->dir_y * pd->move_speed * pd->speed_mod;
	if (!object_collision(md, pd->pos_x, pd->pos_y - pd->dir_x * \
		pd->move_speed * pd->speed_mod))
		pd->pos_y -= pd->dir_x * pd->move_speed * pd->speed_mod;
}

static void		move_right(t_map_data *md, t_player_data *pd)
{
	if (!object_collision(md, pd->pos_x - pd->dir_y * pd->move_speed * \
		pd->speed_mod, pd->pos_y))
		pd->pos_x -= pd->dir_y * pd->move_speed * pd->speed_mod;
	if (!object_collision(md, pd->pos_x, pd->pos_y + pd->dir_x * \
		pd->move_speed * pd->speed_mod))
		pd->pos_y += pd->dir_x * pd->move_speed * pd->speed_mod;
}

void			process_keystates(t_scene *scene)
{
	t_keystates		*ks;
	t_player_data	*pd;
	t_map_data		*md;

	ks = &scene->keystates;
	pd = &scene->player_data;
	md = &scene->map_data;
	set_player_speed(&scene->player_data, &scene->mlx_data);
	if ((ks->kvk_ansi_w == KEY_DOWN || ks->kvk_ansi_s == KEY_DOWN) && \
		(ks->kvk_ansi_a == KEY_DOWN || ks->kvk_ansi_d == KEY_DOWN))
		pd->speed_mod = 0.50;
	else
		pd->speed_mod = 1.0;
	if (ks->kvk_ansi_w == KEY_DOWN)
		move_forward(md, pd);
	if (ks->kvk_ansi_s == KEY_DOWN)
		move_backward(md, pd);
	if (ks->kvk_ansi_a == KEY_DOWN)
		move_left(md, pd);
	if (ks->kvk_ansi_d == KEY_DOWN)
		move_right(md, pd);
	if (ks->kvk_leftarrow == KEY_DOWN)
		turn_left(pd);
	if (ks->kvk_rightarrow == KEY_DOWN)
		turn_right(pd);
}
