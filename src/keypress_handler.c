/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:21:32 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 17:43:57 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "graphics.h"
#include "keycodes.h"

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
		mlx_destroy_window((scene->mlx_data).mlx, (scene->mlx_data).win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KVK_F13 && \
		mlx_image_to_bmp_file(&(scene->mlx_data).frame, "screen.bmp") != 0)
		exit_failure("Failed creating image \"screen.bmp\": %s\n", \
			strerror(errno));
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
	return (0);
}
