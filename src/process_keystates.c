/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keystates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:23:26 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 18:48:08 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_keystates.h"

void		process_keystates(t_scene *scene)
{
	t_keystates		*ks;
	t_player_data	*pd;
	t_map_data		*md;

	ks = &scene->keystates;
	pd = &scene->player_data;
	md = &scene->map_data;
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

void		move_forward(t_map_data *md, t_player_data *pd)
{
	if ((md->map)[(int)pd->pos_y][(int)(pd->pos_x + pd->dir_x * \
		pd->move_speed)] != '1')
		pd->pos_x += pd->dir_x * pd->move_speed * pd->speed_mod;
	if ((md->map)[(int)(pd->pos_y + pd->dir_y * \
		pd->move_speed)][(int)pd->pos_x] != '1')
		pd->pos_y += pd->dir_y * pd->move_speed * pd->speed_mod;
}

void		move_backward(t_map_data *md, t_player_data *pd)
{
	if ((md->map)[(int)pd->pos_y][(int)(pd->pos_x - pd->dir_x * \
		pd->move_speed)] != '1')
		pd->pos_x -= pd->dir_x * pd->move_speed * pd->speed_mod;
	if ((md->map)[(int)(pd->pos_y - pd->dir_y * \
		pd->move_speed)][(int)pd->pos_x] != '1')
		pd->pos_y -= pd->dir_y * pd->move_speed * pd->speed_mod;
}

void		move_left(t_map_data *md, t_player_data *pd)
{
	if ((md->map)[(int)pd->pos_y][(int)(pd->pos_x + pd->dir_y * \
		pd->move_speed)] != '1')
		pd->pos_x += pd->dir_y * pd->move_speed * pd->speed_mod;
	if ((md->map)[(int)(pd->pos_y - pd->dir_x * \
		pd->move_speed)][(int)pd->pos_x] != '1')
		pd->pos_y -= pd->dir_x * pd->move_speed * pd->speed_mod;
}

void		move_right(t_map_data *md, t_player_data *pd)
{
	if ((md->map)[(int)pd->pos_y][(int)(pd->pos_x - pd->dir_y * \
		pd->move_speed)] != '1')
		pd->pos_x -= pd->dir_y * pd->move_speed * pd->speed_mod;
	if ((md->map)[(int)(pd->pos_y + pd->dir_x * \
		pd->move_speed)][(int)pd->pos_x] != '1')
		pd->pos_y += pd->dir_x * pd->move_speed * pd->speed_mod;
}
