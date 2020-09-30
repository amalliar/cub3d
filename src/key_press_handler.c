/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:21:32 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/30 11:11:20 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_press_handler.h"
#include "snd.h"

static inline void	switch_states(int *kd, int *ku)
{
	*kd = KEY_DOWN;
	*ku = KEY_UP;
}

static void			process_movement(int keycode, t_key_states *ks, \
						t_player_data *pd, t_scene *scene)
{
	if (keycode == XK_w)
		switch_states(&ks->xk_w, &ks->xk_s);
	else if (keycode == XK_s)
		switch_states(&ks->xk_s, &ks->xk_w);
	else if (keycode == XK_a)
		switch_states(&ks->xk_a, &ks->xk_d);
	else if (keycode == XK_d)
		switch_states(&ks->xk_d, &ks->xk_a);
	else if (keycode == XK_Left)
		switch_states(&ks->xk_left, &ks->xk_right);
	else if (keycode == XK_Right)
		switch_states(&ks->xk_right, &ks->xk_left);
	else if (keycode == XK_Up)
		switch_states(&ks->xk_up, &ks->xk_down);
	else if (keycode == XK_Down)
		switch_states(&ks->xk_down, &ks->xk_up);
	else if (keycode == XK_Control_L && pd->pos_z == 0)
		pd->pos_z = -200;
	else if (keycode == XK_space && pd->pos_z == 0)
	{
		pd->v0 = sqrt(2 * SV_GRAVITY * PL_JUMP_HEIGHT);
		playSoundFromMemory((scene->sounds)[SND_JUMP], G_SOUNDS_VOLUME);
	}
}

static void			process_weapon_switch(int keycode, t_player_data *pd, \
						t_scene *scene)
{
	if (keycode == XK_1)
		switch_weapon(pd, 0, scene);
	else if (keycode == XK_2)
		switch_weapon(pd, 1, scene);
	else if (keycode == XK_3)
		switch_weapon(pd, 2, scene);
	else if (keycode == XK_4)
		switch_weapon(pd, 3, scene);
}

static void			process_misc(int keycode, t_scene *scene)
{
	if (keycode == XK_Escape)
	{
		endAudio();
		SDL_Quit();
		mlx_destroy_window((scene->mlx_data).mlx, (scene->mlx_data).win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == XK_F12)
		take_screenshot(scene);
	else if (keycode == XK_e)
		process_interact_request(scene, &scene->player_data, &scene->map_data);
}

int					key_press_handler(int keycode, t_scene *scene)
{
	t_player_data		*pd;
	t_key_states		*ks;

	ks = &scene->key_states;
	pd = &scene->player_data;
	process_misc(keycode, scene);
	if (scene->game_state != GS_NORMAL)
		return (0);
	process_movement(keycode, ks, pd, scene);
	process_weapon_switch(keycode, pd, scene);
	return (0);
}
