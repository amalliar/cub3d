/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:26:43 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/17 21:43:46 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "events.h"
#include "graphics.h"
#include "render_scene.h"

static int		render_next_frame(t_scene *scene)
{
	clock_t			r_start;
	t_mlx_data		*mlx_data;

	r_start = clock();
	mlx_data = &scene->mlx_data;
	process_keystates(scene);
	render_textures(scene);
	render_sprites(scene);
	if (scene->render_mode == SCREENSHOT)
	{
		if (mlx_image_to_bmp_file(&mlx_data->frame, "screen.bmp"))
			exit_failure("Failed creating image \"screen.bmp\": %s\n", \
			strerror(errno));
		exit(EXIT_SUCCESS);
	}
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
		(*mlx_data).frame.img, 0, 0);
	mlx_data->frame_time = (double)(clock() - r_start) / CLOCKS_PER_SEC;
	return (0);
}

static void		init_frame(t_scene *scene)
{
	t_mlx_data		*mlx_data;
	t_mlx_image		*frame;

	mlx_data = &scene->mlx_data;
	frame = &mlx_data->frame;
	frame->width = mlx_data->width;
	frame->height = mlx_data->height;
	if (!(frame->img = mlx_new_image(mlx_data->mlx, frame->width, \
		frame->height)))
		exit_failure("Failed creating mlx image instance: %s\n", \
			strerror(errno));
	frame->addr = mlx_get_data_addr(frame->img, &frame->bits_per_pixel, \
		&frame->line_length, &frame->endian);
	if (!((*scene).player_data.zbuffer = \
		malloc(frame->width * sizeof(double))))
		exit_failure("%s\n", strerror(errno));
}

void			render_scene(t_scene *scene, int mode)
{
	t_mlx_data		*mlx_data;

	mlx_data = &scene->mlx_data;
	init_frame(scene);
	if (mode == SCREENSHOT)
		render_next_frame(scene);
	mlx_data->win = mlx_new_window(mlx_data->mlx, mlx_data->width, \
		mlx_data->height, MLX_WINDOW_TITLE);
	mlx_loop_hook(mlx_data->mlx, render_next_frame, scene);
	mlx_do_key_autorepeatoff(mlx_data->mlx);
	mlx_hook(mlx_data->win, KEY_PRESS, KEY_PRESS_MASK, keypress_handler, scene);
	mlx_hook(mlx_data->win, KEY_RELEASE, KEY_RELEASE_MASK, \
		keyrelease_handler, scene);
	mlx_hook(mlx_data->win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, \
		winclose_handler, scene);
	mlx_loop(mlx_data->mlx);
}
