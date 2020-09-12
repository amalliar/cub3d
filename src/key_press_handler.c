/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:21:32 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 18:59:51 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_press_handler.h"

static void		switch_states(int *kd, int *ku)
{
	*kd = KEY_DOWN;
	*ku = KEY_UP;
}

static void		process_movement(int keycode, t_key_states *ks, \
					t_player_data *pd)
{
	if (keycode == KVK_ANSI_W)
		switch_states(&ks->kvk_ansi_w, &ks->kvk_ansi_s);
	else if (keycode == KVK_ANSI_S)
		switch_states(&ks->kvk_ansi_s, &ks->kvk_ansi_w);
	else if (keycode == KVK_ANSI_A)
		switch_states(&ks->kvk_ansi_a, &ks->kvk_ansi_d);
	else if (keycode == KVK_ANSI_D)
		switch_states(&ks->kvk_ansi_d, &ks->kvk_ansi_a);
	else if (keycode == KVK_LEFTARROW)
		switch_states(&ks->kvk_leftarrow, &ks->kvk_rightarrow);
	else if (keycode == KVK_RIGHTARROW)
		switch_states(&ks->kvk_rightarrow, &ks->kvk_leftarrow);
	else if (keycode == KVK_UPARROW)
		switch_states(&ks->kvk_uparrow, &ks->kvk_downarrow);
	else if (keycode == KVK_DOWNARROW)
		switch_states(&ks->kvk_downarrow, &ks->kvk_uparrow);
	else if (keycode == KVK_CONTROL && pd->pos_z == 0)
		pd->pos_z = -200;
	else if (keycode == KVK_SPACE && pd->pos_z == 0)
		pd->v0 = sqrt(2 * SV_GRAVITY * PL_JUMP_HEIGHT);
}

static void		process_weapon_switch(int keycode, t_player_data *pd)
{
	if (keycode == KVK_ANSI_1)
		switch_weapon(pd, 0);
	else if (keycode == KVK_ANSI_2)
		switch_weapon(pd, 1);
	else if (keycode == KVK_ANSI_3)
		switch_weapon(pd, 2);
	else if (keycode == KVK_ANSI_4)
		switch_weapon(pd, 3);
}

static void		process_misc(int keycode, t_scene *scene)
{
	if (keycode == KVK_ESCAPE)
	{
		mlx_destroy_window((scene->mlx_data).mlx, (scene->mlx_data).win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KVK_F13)
		take_screenshot(scene);
	else if (keycode == KVK_ANSI_E)
		process_interact_request(scene);
}

int				key_press_handler(int keycode, t_scene *scene)
{
	t_player_data		*pd;
	t_key_states		*ks;

	ks = &scene->key_states;
	pd = &scene->player_data;
	process_movement(keycode, ks, pd);
	process_weapon_switch(keycode, pd);
	process_misc(keycode, scene);
	return (0);
}
