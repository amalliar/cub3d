/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:21:32 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/07 15:38:48 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"

int		keypress_handler(int keycode, t_scene *scene)
{
	t_keystates		*ks;

	ks = &scene->keystates;
	if (keycode == KVK_ESCAPE)
	{
		mlx_destroy_window((*scene).mlx_data.mlx, (*scene).mlx_data.win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KVK_ANSI_W)
		ks->kvk_ansi_w = KEY_DOWN;
	else if (keycode == KVK_ANSI_A)
		ks->kvk_ansi_a = KEY_DOWN;
	else if (keycode == KVK_ANSI_S)
		ks->kvk_ansi_s = KEY_DOWN;
	else if (keycode == KVK_ANSI_D)
		ks->kvk_ansi_d = KEY_DOWN;
	else if (keycode == KVK_LEFTARROW)
		ks->kvk_leftarrow = KEY_DOWN;
	else if (keycode == KVK_RIGHTARROW)
		ks->kvk_rightarrow = KEY_DOWN;
	return (0);
}
