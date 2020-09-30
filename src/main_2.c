/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 04:36:04 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/30 11:02:31 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		init_mlx_data(t_mlx_data *mlx_data)
{
	if (!(mlx_data->mlx = mlx_init()))
		exit_failure("Failed creating mlx instance\n");
	mlx_data->win = NULL;
	mlx_get_screen_size(mlx_data->mlx, &mlx_data->width, &mlx_data->height);
	if (mlx_data->width < G_MLX_WINDOW_WIDTH || \
		mlx_data->height < G_MLX_WINDOW_HEIGHT)
		exit_failure("Resolution %sx%s is unsupported by this screen.\n", \
			ft_itoa(G_MLX_WINDOW_WIDTH, 10), ft_itoa(G_MLX_WINDOW_HEIGHT, 10));
	mlx_data->width = G_MLX_WINDOW_WIDTH;
	mlx_data->height = G_MLX_WINDOW_HEIGHT;
}

void		init_key_and_button_states(t_key_states *ks, \
					t_button_states *bs)
{
	ks->xk_w = KEY_UP;
	ks->xk_a = KEY_UP;
	ks->xk_s = KEY_UP;
	ks->xk_d = KEY_UP;
	ks->xk_left = KEY_UP;
	ks->xk_right = KEY_UP;
	ks->xk_up = KEY_UP;
	ks->xk_down = KEY_UP;
	bs->mb_left = KEY_UP;
	bs->mb_right = KEY_UP;
	bs->mb_middle = KEY_UP;
	bs->mb_wheel_up = KEY_UP;
	bs->mb_wheel_down = KEY_UP;
}

void		init_player_data(t_player_data *pd)
{
	pd->pos_x = -1;
	pd->v0 = 0;
	pd->facecount = 0;
	pd->r_facetimer = 0;
	pd->faceframe = 1;
	(pd->effects).r_bj_evil_grin = 0;
	(pd->effects).r_item_pickup = 0;
	(pd->effects).r_player_hit = 0;
	(pd->effects).r_player_dead = 0;
	(pd->effects).r_player_respawn = 0;
}
