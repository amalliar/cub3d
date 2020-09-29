/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_effects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 00:35:52 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 08:12:26 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "graphics.h"
#include "render_scene.h"

static int		process_full_window_effects(t_mlx_data *mlx_data, \
					t_effects *effects)
{
	t_point		res;
	double		opacity;

	res.x = G_MLX_WINDOW_WIDTH;
	res.y = G_MLX_WINDOW_HEIGHT - 1;
	if (effects->r_player_dead)
	{
		opacity = (double)(clock() - effects->r_player_dead) / CLOCKS_PER_SEC;
		if (opacity > 2)
			effects->r_player_dead = 0;
		else
			add_color_mask(&mlx_data->frame, res, CLR_BLOOD, opacity / 2);
	}
	else if (effects->r_player_respawn)
	{
		opacity = \
			(double)(clock() - effects->r_player_respawn) / CLOCKS_PER_SEC;
		if (opacity > 2)
			effects->r_player_respawn = 0;
		else
			add_color_mask(&mlx_data->frame, res, CLR_BLOOD, 1 - opacity / 2);
	}
	else
		return (0);
	return (1);
}

static void		process_game_window_effects(t_mlx_data *mlx_data, \
					t_effects *effects)
{
	t_point		res;
	double		opacity;

	res.x = G_GAME_WINDOW_WIDTH;
	res.y = G_GAME_WINDOW_HEIGHT;
	if (effects->r_player_hit)
	{
		opacity = (double)(clock() - effects->r_player_hit) / CLOCKS_PER_SEC;
		if (opacity > 0.5)
			effects->r_player_hit = 0;
		else
			add_color_mask(&mlx_data->frame, res, CLR_BLOOD, \
				(1 - opacity * 2) / 4);
	}
	else if (effects->r_item_pickup)
	{
		opacity = (double)(clock() - effects->r_item_pickup) / CLOCKS_PER_SEC;
		if (opacity > 0.5)
			effects->r_item_pickup = 0;
		else
			add_color_mask(&mlx_data->frame, res, CLR_YELLOW, \
				(1 - opacity * 2) / 4);
	}
}

void			process_effects(t_scene *scene)
{
	t_mlx_data	*mlx_data;
	t_effects	*effects;

	mlx_data = &scene->mlx_data;
	effects = &(scene->player_data).effects;
	if (process_full_window_effects(mlx_data, effects) == 0)
		process_game_window_effects(mlx_data, effects);
}
