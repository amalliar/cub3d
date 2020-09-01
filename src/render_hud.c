/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 07:21:24 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/02 00:51:44 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "graphics.h"

void		render_hud(t_scene *scene)
{
	t_mlx_data		*mlx_data;
	t_player_data	*pd;
	t_mlx_image		*hud;
	t_point			p0;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	hud = (*scene).textures.hud;
	p0.x = 0;
	p0.y = mlx_data->height - HUD_HEIGHT;
	latch_image(&mlx_data->frame, hud + 10, p0, HUD_SCALE);
	p0.x = 14 * HUD_SCALE;
	p0.y = mlx_data->height - HUD_HEIGHT + 14 * HUD_SCALE;
	latch_number(&mlx_data->frame, hud, pd->level, p0);
	p0.x += 66.5 * HUD_SCALE;
	latch_number(&mlx_data->frame, hud, pd->score, p0);
	p0.x += 24 * HUD_SCALE;
	latch_number(&mlx_data->frame, hud, pd->lives, p0);
	p0.x += 71 * HUD_SCALE;
	latch_number(&mlx_data->frame, hud, pd->health, p0);
	p0.x += 42 * HUD_SCALE;
	latch_number(&mlx_data->frame, hud, pd->ammo, p0);
}
