/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 07:21:24 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/09 14:42:38 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "graphics.h"

static void		draw_face(t_scene *scene)
{
	t_mlx_data		*mlx_data;
	t_player_data	*pd;
	t_mlx_image		*faces;
	t_point			p0;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	faces = (*scene).textures.faces;
	p0.x = 129 * HUD_SCALE;
	p0.y = mlx_data->height - HUD_HEIGHT + 9;
	latch_image(&mlx_data->frame, faces + 3 * ((100 - pd->health) / 16) + \
		pd->faceframe, p0, HUD_SCALE);
}

static void		update_face(t_scene *scene)
{
	static int			facecount = 0;
	static clock_t		r_timer = 0;
	t_mlx_data			*mlx_data;
	t_player_data		*pd;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	facecount += clock();
	if (facecount * mlx_data->frame_time * 10 > rand() && \
		(clock() - r_timer) / CLOCKS_PER_SEC >= 1.0)
	{
		pd->faceframe = (rand() % 4);
		if (pd->faceframe == 3)
			pd->faceframe = 1;
		facecount = 0;
		r_timer = clock();
	}
}

void			render_hud(t_scene *scene)
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
	update_face(scene);
	draw_face(scene);
	p0.x += 71 * HUD_SCALE;
	latch_number(&mlx_data->frame, hud, pd->health, p0);
	p0.x += 42 * HUD_SCALE;
	latch_number(&mlx_data->frame, hud, pd->ammo, p0);
}
