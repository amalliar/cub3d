/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:25:47 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/30 19:32:07 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define XK_MISCELLANY
#define XK_LATIN1

#include <X11/keysymdef.h>
#include "cub3d.h"

int		key_release_handler(int keycode, t_scene *scene)
{
	t_key_states		*ks;

	ks = &scene->key_states;
	if (keycode == XK_w)
		ks->xk_w = KEY_UP;
	else if (keycode == XK_a)
		ks->xk_a = KEY_UP;
	else if (keycode == XK_s)
		ks->xk_s = KEY_UP;
	else if (keycode == XK_d)
		ks->xk_d = KEY_UP;
	else if (keycode == XK_Left)
		ks->xk_left = KEY_UP;
	else if (keycode == XK_Right)
		ks->xk_right = KEY_UP;
	else if (keycode == XK_Up)
		ks->xk_up = KEY_UP;
	else if (keycode == XK_Down)
		ks->xk_down = KEY_UP;
	else if (keycode == XK_Control_L && (scene->player_data).pos_z < 0)
		(scene->player_data).pos_z = 0;
	return (0);
}
