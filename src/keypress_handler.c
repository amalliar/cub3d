/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:21:32 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/04 07:27:59 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "graphics.h"

static void		switch_states(int *kd, int *ku)
{
	*kd = KEY_DOWN;
	*ku = KEY_UP;
}

int				keypress_handler(int keycode, t_scene *scene)
{
	t_keystates		*ks;

	ks = &scene->keystates;
	if (keycode == KVK_ESCAPE)
	{
		mlx_destroy_window((*scene).mlx_data.mlx, (*scene).mlx_data.win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KVK_F13)
		take_screenshot(scene);
	else if (keycode == KVK_ANSI_W)
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
	return (0);
}
