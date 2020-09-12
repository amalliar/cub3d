/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 07:21:24 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 22:33:06 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "render_hud.h"

static void		draw_stats(t_scene *scene)
{
	t_mlx_data		*mlx_data;
	t_player_data	*pd;
	t_mlx_image		*hud;
	t_point			p0;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	hud = (scene->textures).hud;
	p0.x = 0;
	p0.y = mlx_data->height - G_HUD_HEIGHT;
	latch_image(&mlx_data->frame, hud + 10, p0, G_HUD_SCALE);
	p0.x = 14 * G_HUD_SCALE;
	p0.y = mlx_data->height - G_HUD_HEIGHT + 14 * G_HUD_SCALE;
	latch_number(&mlx_data->frame, hud, pd->level, p0);
	p0.x += 66.5 * G_HUD_SCALE;
	latch_number(&mlx_data->frame, hud, pd->score, p0);
	p0.x += 24 * G_HUD_SCALE;
	latch_number(&mlx_data->frame, hud, pd->lives, p0);
	p0.x += 71 * G_HUD_SCALE;
	latch_number(&mlx_data->frame, hud, pd->health, p0);
	p0.x += 42 * G_HUD_SCALE;
	latch_number(&mlx_data->frame, hud, pd->ammo, p0);
}

static void		update_face(t_scene *scene)
{
	t_mlx_data			*mlx_data;
	t_player_data		*pd;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	pd->facecount += clock();
	if (pd->facecount * mlx_data->frame_time * 10 > rand() && \
		(double)(clock() - pd->r_facetimer) / CLOCKS_PER_SEC >= 1.0)
	{
		pd->faceframe = (rand() % 4);
		if (pd->faceframe == 3)
			pd->faceframe = 1;
		pd->facecount = 0;
		pd->r_facetimer = clock();
	}
}

static void		draw_face(t_scene *scene)
{
	t_mlx_data		*mlx_data;
	t_player_data	*pd;
	t_mlx_image		*faces;
	t_point			p0;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	faces = (*scene).textures.faces;
	p0.x = 129 * G_HUD_SCALE;
	p0.y = mlx_data->height - G_HUD_HEIGHT + 2.2 * G_HUD_SCALE;
	if ((*pd).effects.r_bj_evil_grin)
	{
		if ((clock() - (*pd).effects.r_bj_evil_grin) / CLOCKS_PER_SEC <= 2.0)
		{
			latch_image(&mlx_data->frame, faces + 21, p0, G_HUD_SCALE);
			return ;
		}
		(*pd).effects.r_bj_evil_grin = 0;
		pd->faceframe = 1;
		pd->facecount = 0;
		pd->r_facetimer = clock();
	}
	latch_image(&mlx_data->frame, \
		faces + 3 * ((100 - pd->health) / 16) + pd->faceframe, p0, G_HUD_SCALE);
}

static void		draw_weapon(t_scene *scene)
{
	t_mlx_data		*mlx_data;
	t_weapon		*weapon;
	t_point			p0;

	mlx_data = &scene->mlx_data;
	weapon = (*scene).player_data.active_weapon;
	p0.x = 247.5 * G_HUD_SCALE;
	p0.y = mlx_data->height - G_HUD_HEIGHT + 5 * G_HUD_SCALE;
	latch_image(&mlx_data->frame, weapon->hudpic, p0, G_HUD_SCALE);
	p0.x = G_GAME_WINDOW_WIDTH / 2 - 32 * G_HUD_SCALE * PL_WEAPON_SCALE;
	p0.y = mlx_data->height - G_HUD_HEIGHT - 63.9 * G_HUD_SCALE * PL_WEAPON_SCALE;
	latch_image(&mlx_data->frame, weapon->frames + weapon->frame, \
		p0, G_HUD_SCALE * PL_WEAPON_SCALE);
}

void			render_hud(t_scene *scene)
{
	draw_stats(scene);
	update_face(scene);
	draw_face(scene);
	draw_weapon(scene);
	draw_crosshair(scene);
}
