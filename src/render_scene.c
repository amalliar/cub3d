/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:26:43 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/10 18:45:15 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "events.h"
#include "graphics.h"

#include "colors.h"

static void		init_vars(int x, int width, t_player_data *pd)
{
	pd->camera_x = 2 * x / (double)width - 1;
	pd->ray_dir_x = pd->dir_x + pd->plane_x * pd->camera_x;
	pd->ray_dir_y = pd->dir_y + pd->plane_y * pd->camera_x;
	pd->map_x = (int)pd->pos_x;
	pd->map_y = (int)pd->pos_y;
	pd->delta_dist_x = fabs(1.0 / pd->ray_dir_x);
	pd->delta_dist_y = fabs(1.0 / pd->ray_dir_y);
	pd->hit = 0;
}

static void		calc_step_and_sidedist(t_player_data *pd) {
	if (pd->ray_dir_x < 0)
	{
		pd->step_x = -1;
		pd->side_dist_x = (pd->pos_x - pd->map_x) * pd->delta_dist_x;
	}
	else
	{
		pd->step_x = 1;
		pd->side_dist_x = (pd->map_x + 1.0 - pd->pos_x) * pd->delta_dist_x;
	}
	if (pd->ray_dir_y < 0)
	{
		pd->step_y = -1;
		pd->side_dist_y = (pd->pos_y - pd->map_y) * pd->delta_dist_y;
	}
	else
	{
		pd->step_y = 1;
		pd->side_dist_y = (pd->map_y + 1.0 - pd->pos_y) * pd->delta_dist_y;
	}
}

static void		perform_dda(t_player_data *pd, t_map_data *md)
{
	while (pd->hit == 0)
	{
		if (pd->side_dist_x < pd->side_dist_y)
		{
			pd->side_dist_x += pd->delta_dist_x;
			pd->map_x += pd->step_x;
			pd->side = 0;
		}
		else
		{
			pd->side_dist_y += pd->delta_dist_y;
			pd->map_y += pd->step_y;
			pd->side = 1;
		}
		if ((md->map)[pd->map_y][pd->map_x] == '1')
			pd->hit = 1;
	}
}


static void		calc_draw_start_end(int h, t_player_data *pd)
{
	if (pd->side == 0)
		pd->perp_wall_dist = (pd->map_x - pd->pos_x + (1 - pd->step_x) / 2) / pd->ray_dir_x;
	else
		pd->perp_wall_dist = (pd->map_y - pd->pos_y + (1 - pd->step_y) / 2) / pd->ray_dir_y;
	pd->line_height = (int)(h / pd->perp_wall_dist);
	pd->draw_start = -pd->line_height / 2 + h / 2;
	if (pd->draw_start < 0 || pd->draw_start >= h)
		pd->draw_start = 0;
	pd->draw_end = pd->line_height / 2 + h / 2;
	if (pd->draw_end >= h || pd->draw_end < 0)
		pd->draw_end = h - 1;
}


static void		process_keystates(t_keystates *ks, t_player_data *pd, t_map_data *md)
{
	double		speed_mod;

	if ((ks->kvk_ansi_w == KEY_DOWN || ks->kvk_ansi_s == KEY_DOWN) && (ks->kvk_ansi_a == KEY_DOWN || ks->kvk_ansi_d == KEY_DOWN))
		speed_mod = 0.50;
	else
		speed_mod = 1.0;
	if (ks->kvk_ansi_w == KEY_DOWN)
	{
		if ((md->map)[(int)pd->pos_y][(int)(pd->pos_x + pd->dir_x * pd->move_speed)] != '1')
			pd->pos_x += pd->dir_x * pd->move_speed * speed_mod;
		if ((md->map)[(int)(pd->pos_y + pd->dir_y * pd->move_speed)][(int)pd->pos_x] != '1')
			pd->pos_y += pd->dir_y * pd->move_speed * speed_mod;
	}
	if (ks->kvk_ansi_s == KEY_DOWN)
	{
		if ((md->map)[(int)pd->pos_y][(int)(pd->pos_x - pd->dir_x * pd->move_speed)] != '1')
			pd->pos_x -= pd->dir_x * pd->move_speed * speed_mod;
		if ((md->map)[(int)(pd->pos_y - pd->dir_y * pd->move_speed)][(int)pd->pos_x] != '1')
			pd->pos_y -= pd->dir_y * pd->move_speed * speed_mod;
	}
	if (ks->kvk_ansi_d == KEY_DOWN)
	{
		if ((md->map)[(int)pd->pos_y][(int)(pd->pos_x -pd->dir_y * pd->move_speed)] != '1')
			pd->pos_x -= pd->dir_y * pd->move_speed * speed_mod;
		if ((md->map)[(int)(pd->pos_y + pd->dir_x * pd->move_speed)][(int)pd->pos_x] != '1')
			pd->pos_y += pd->dir_x * pd->move_speed * speed_mod;

	}
	if (ks->kvk_ansi_a == KEY_DOWN)
	{
		if ((md->map)[(int)pd->pos_y][(int)(pd->pos_x +pd->dir_y * pd->move_speed)] != '1')
			pd->pos_x += pd->dir_y * pd->move_speed * speed_mod;
		if ((md->map)[(int)(pd->pos_y - pd->dir_x * pd->move_speed)][(int)pd->pos_x] != '1')
			pd->pos_y -= pd->dir_x * pd->move_speed * speed_mod;
	}
	if (ks->kvk_leftarrow == KEY_DOWN)
	{
		pd->old_dir_x = pd->dir_x;
		pd->dir_x = pd->dir_x * cos(-pd->rot_speed) - pd->dir_y * sin(-pd->rot_speed);
		pd->dir_y = pd->old_dir_x * sin(-pd->rot_speed) + pd->dir_y * cos(-pd->rot_speed);
		pd->old_plane_x = pd->plane_x;
		pd->plane_x = pd->plane_x * cos(-pd->rot_speed) - pd->plane_y * sin(-pd->rot_speed);
		pd->plane_y = pd->old_plane_x * sin(-pd->rot_speed) + pd->plane_y * cos(-pd->rot_speed);
	}
	if (ks->kvk_rightarrow == KEY_DOWN)
	{
		pd->old_dir_x = pd->dir_x;
		pd->dir_x = pd->dir_x * cos(pd->rot_speed) - pd->dir_y * sin(pd->rot_speed);
		pd->dir_y = pd->old_dir_x * sin(pd->rot_speed) + pd->dir_y * cos(pd->rot_speed);
		pd->old_plane_x = pd->plane_x;
		pd->plane_x = pd->plane_x * cos(pd->rot_speed) - pd->plane_y * sin(pd->rot_speed);
		pd->plane_y = pd->old_plane_x * sin(pd->rot_speed) + pd->plane_y * cos(pd->rot_speed);
	}
}

static int		render_next_frame(t_scene *scene)
{
	t_mlx_data		*mlx_data;
	t_player_data	*player_data;
	int				x;
	int				color;

	mlx_data = &scene->mlx_data;
	player_data = &scene->player_data;
	process_keystates(&scene->keystates, player_data, &scene->map_data);
	x = 0;
	while (x < mlx_data->width)
	{
		init_vars(x, mlx_data->width, player_data);
		calc_step_and_sidedist(player_data);
		perform_dda(player_data, &scene->map_data);
		calc_draw_start_end(mlx_data->height, player_data);
		color = ORANGE;
		if (player_data->side == 1)
			color = add_shade(0.45, color);
		if (player_data->draw_start > 0)
			drawverline(&mlx_data->frame, x, 0, player_data->draw_start - 1, (*scene).colors.ceilling);
		drawverline(&mlx_data->frame, x, player_data->draw_start, player_data->draw_end, color);
		if (player_data->draw_end < mlx_data->height - 1)
			drawverline(&mlx_data->frame, x, player_data->draw_end + 1, mlx_data->height - 1, (*scene).colors.floor);
		++x;
	}
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, (mlx_data->frame).img, 0, 0);
	return (0);
}

void		render_scene(t_scene *scene)
{
	t_mlx_data	*mlx_data;

	mlx_data = &(*scene).mlx_data;
	mlx_data->win = mlx_new_window(mlx_data->mlx, mlx_data->width, \
		mlx_data->height, MLX_WINDOW_TITLE);
	(mlx_data->frame).img = mlx_new_image(mlx_data->mlx, mlx_data->width, \
		mlx_data->height);
	(mlx_data->frame).addr = mlx_get_data_addr((mlx_data->frame).img, &(mlx_data->frame).bits_per_pixel, \
		&(mlx_data->frame).line_length, &(mlx_data->frame).endian);
	mlx_loop_hook(mlx_data->mlx, render_next_frame, scene);
	mlx_do_key_autorepeatoff(mlx_data->mlx);
	mlx_hook(mlx_data->win, KEY_PRESS, KEY_PRESS_MASK, keypress_handler, scene);
	mlx_hook(mlx_data->win, KEY_RELEASE, KEY_RELEASE_MASK, keyrelease_handler, scene);
	mlx_hook(mlx_data->win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, winclose_handler, scene);
	mlx_loop(mlx_data->mlx);
}
