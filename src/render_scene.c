/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:26:43 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/29 11:16:41 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"

void			render_fps_counter(t_mlx_data *mlx_data)
{
	static clock_t	r_timer = 0;
	static int		frames = 0;
	char			*str;

	if (SV_SHOW_FPS)
	{
		str = ft_itoa(mlx_data->frames_per_second, 10);
		mlx_string_put(mlx_data->mlx, mlx_data->win, 1, 5, CLR_YELLOW, str);
		free(str);
	}
	if ((clock() - r_timer) / CLOCKS_PER_SEC >= 1)
	{
		mlx_data->frames_per_second = frames;
		frames = 0;
		r_timer = clock();
	}
	++frames;
}

static int		render_next_frame(t_scene *scene)
{
	clock_t			r_start;
	t_mlx_data		*mlx_data;

	if (process_game_state(scene) != GS_NORMAL)
		return (0);
	mlx_data = &scene->mlx_data;
	r_start = clock();
	process_key_states(scene);
	process_mouse_motion(scene);
	process_physics(scene);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, mlx_data->win);
	render_floor_and_ceiling(scene);
	render_walls(scene);
	render_sprites(scene);
	render_hud(scene);
	attempt_item_pickup(scene);
	process_enemie_states(scene);
	process_effects(scene);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
		(mlx_data->frame).img, 0, 0);
	render_fps_counter(mlx_data);
	mlx_data->frame_time = (double)(clock() - r_start) / CLOCKS_PER_SEC;
	return (0);
}

void			init_frame(t_scene *scene)
{
	t_mlx_data		*mlx_data;
	t_mlx_image		*frame;
	t_player_data	*pd;

	mlx_data = &scene->mlx_data;
	frame = &mlx_data->frame;
	pd = &scene->player_data;
	frame->width = G_GAME_WINDOW_WIDTH;
	frame->height = G_GAME_WINDOW_HEIGHT;
	if (!(frame->img = mlx_new_image(mlx_data->mlx, \
		mlx_data->width, mlx_data->height)))
		exit_failure("Failed creating mlx image instance: %s\n", \
			strerror(errno));
	frame->addr = mlx_get_data_addr(frame->img, &frame->bits_per_pixel, \
		&frame->line_size, &frame->endian);
	if (!(pd->zbuffer = malloc(frame->width * sizeof(double))))
		exit_failure("%s\n", strerror(errno));
	scene->render_started = 1;
}

void			render_scene(t_scene *scene)
{
	t_mlx_data		*mlx_data;

	mlx_data = &scene->mlx_data;
	init_frame(scene);
	if (!(mlx_data->win = mlx_new_window(mlx_data->mlx, mlx_data->width, \
		mlx_data->height, G_MLX_WINDOW_TITLE)))
		exit_failure("Failed creating mlx window instance: %s\n", \
			strerror(errno));
	mlx_do_key_autorepeatoff(mlx_data->mlx);
	mlx_hook(mlx_data->win, KEY_PRESS, KEY_PRESS_MASK, \
		key_press_handler, scene);
	mlx_hook(mlx_data->win, KEY_RELEASE, KEY_RELEASE_MASK, \
		key_release_handler, scene);
	mlx_hook(mlx_data->win, BUTTON_PRESS, BUTTON_PRESS_MASK, \
		button_press_handler, scene);
	mlx_hook(mlx_data->win, BUTTON_RELEASE, BUTTON_RELEASE_MASK, \
		button_release_handler, scene);
	mlx_hook(mlx_data->win, EXPOSE, EXPOSURE_MASK, \
		expose_handler, scene);
	mlx_hook(mlx_data->win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, \
		winclose_handler, scene);
	mlx_loop_hook(mlx_data->mlx, render_next_frame, scene);
	mlx_loop(mlx_data->mlx);
}
