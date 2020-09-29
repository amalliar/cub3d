/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_game_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 05:25:54 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/29 12:19:31 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"

static void		render_death_animation(t_scene *scene)
{
	t_effects		*effects;
	t_mlx_data		*mlx_data;

	mlx_data = &scene->mlx_data;
	effects = &(scene->player_data).effects;
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, mlx_data->win);
	render_floor_and_ceiling(scene);
	render_walls(scene);
	render_sprites(scene);
	render_hud(scene);
	process_effects(scene);
	if (effects->r_player_dead == 0)
	{
		scene->game_state = GS_RESTART;
		return ;
	}
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
		(mlx_data->frame).img, 0, 0);
	render_fps_counter(mlx_data);
}

static void		restart_level(t_scene *scene)
{
	t_player_data	*pd;

	pd = &scene->player_data;
	if (--pd->lives < 0)
	{
		scene->game_state = GS_END;
		return ;
	}
	pd->health = 100;
	pd->ammo = (pd->ammo < 8) ? 8 : pd->ammo;
	pd->score = (pd->score < 5000) ? 0 : pd->score - 5000;
	pd->pos_x = pd->default_pos_x;
	pd->pos_y = pd->default_pos_y;
	pd->pos_z = 0;
	pd->pitch = 0;
	pd->dir_x = pd->default_dir_x;
	pd->dir_y = pd->default_dir_y;
	pd->plane_x = pd->default_plane_x;
	pd->plane_y = pd->default_plane_y;
	pd->active_weapon->state = IDLE;
	pd->active_weapon->frame = 0;
	pd->active_weapon = pd->weapons + 1;
	(pd->effects).r_player_respawn = clock();
	scene->game_state = GS_RESPAWN;
}

static void		render_respawn_animation(t_scene *scene)
{
	t_mlx_data		*mlx_data;
	t_player_data	*pd;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, mlx_data->win);
	render_floor_and_ceiling(scene);
	render_walls(scene);
	render_sprites(scene);
	render_hud(scene);
	process_effects(scene);
	if ((pd->effects).r_player_respawn == 0)
	{
		mlx_mouse_move(mlx_data->win, G_CENTER_X, G_CENTER_Y);
		scene->game_state = GS_NORMAL;
		playMusicFromMemory((scene->music)[pd->level - 1], G_MUSIC_VOLUME);
		return ;
	}
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
		(mlx_data->frame).img, 0, 0);
	render_fps_counter(mlx_data);
}

static void		render_endgame_screen(t_scene *scene)
{
	t_mlx_data		*mlx_data;
	t_point			p0;
	t_point			p1;
	t_point			res;

	playSoundFromMemory((scene->sounds)[SND_ROSTER], G_SOUNDS_VOLUME);
	mlx_data = &scene->mlx_data;
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, mlx_data->win);
	init_point(&res, G_MLX_WINDOW_WIDTH, G_MLX_WINDOW_HEIGHT);
	add_color_mask(&mlx_data->frame, res, CLR_BLOOD, 1);
	init_point(&p0, 0, 64 * G_HUD_SCALE);
	init_point(&p1, G_GAME_WINDOW_WIDTH, p0.y + 16 * G_HUD_SCALE);
	draw_rectangle(&mlx_data->frame, p0, p1, CLR_BLACK);
	p0.y = p1.y + G_HUD_SCALE / 2 + 2;
	p1.y = p0.y + G_HUD_SCALE / 2;
	draw_rectangle(&mlx_data->frame, p0, p1, CLR_BLACK);
	p0.x = G_GAME_WINDOW_WIDTH / 2 - ((scene->textures).menu)[0].width * \
		(G_HUD_SCALE / 1.5) / 2;
	p0.y = 61 * G_HUD_SCALE;
	latch_image(&mlx_data->frame, (scene->textures).menu, p0, \
		G_HUD_SCALE / 1.5);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
		(mlx_data->frame).img, 0, 0);
	scene->game_state = GS_HALT;
}

int				process_game_state(t_scene *scene)
{
	if (scene->game_state == GS_NORMAL)
		return (GS_NORMAL);
	else if (scene->game_state == GS_DEATH)
		render_death_animation(scene);
	else if (scene->game_state == GS_RESTART)
		restart_level(scene);
	else if (scene->game_state == GS_RESPAWN)
		render_respawn_animation(scene);
	else if (scene->game_state == GS_END)
		render_endgame_screen(scene);
	return (scene->game_state);
}
