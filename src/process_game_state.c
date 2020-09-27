/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_game_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 05:25:54 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/27 06:26:50 by amalliar         ###   ########.fr       */
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
}

static void		restart_level(t_scene *scene)
{
	t_player_data	*pd;
	t_effects		*effects;

	pd = &scene->player_data;
	effects = &pd->effects;
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
	pd->active_weapon->frame = 0;
	pd->active_weapon = pd->weapons + 1;
	effects->r_player_respawn = clock();
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
}

static void		render_endgame_screen(t_scene *scene)
{
	playSoundFromMemory((scene->sounds)[SND_ROSTER], G_SOUNDS_VOLUME);
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
