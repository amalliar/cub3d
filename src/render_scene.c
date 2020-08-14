/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:26:43 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/14 20:21:25 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "events.h"
#include "graphics.h"

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
	t_mlx_image		*texture;
	t_player_data	*pd;
	t_point			p0;
	t_point			p1;
	int				color;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	process_keystates(&scene->keystates, pd, &scene->map_data);
	p0.x = 0;
	while (p0.x < mlx_data->width)
	{
		init_vars(p0.x, mlx_data->width, pd);
		calc_step_and_sidedist(pd);
		perform_dda(pd, &scene->map_data);
		calc_draw_start_end(mlx_data->height, pd);
		if (pd->side == 0)
		{
			if (pd->ray_dir_x >= 0)
				texture = &(*scene).textures.walls.east;
			else
				texture = &(*scene).textures.walls.west;
		}
		else
		{
			if (pd->ray_dir_y >= 0)
				texture = &(*scene).textures.walls.south;
			else
				texture = &(*scene).textures.walls.north;
		}
		if (pd->side == 0)
			pd->wall_x = pd->pos_y + pd->perp_wall_dist * pd->ray_dir_y;
		else
			pd->wall_x = pd->pos_x + pd->perp_wall_dist * pd->ray_dir_x;
		pd->wall_x -= floor((pd->wall_x));
		pd->tex_x = (int)(pd->wall_x * (double)texture->width);
		if (pd->side == 0 && pd->ray_dir_x > 0)
			pd->tex_x = texture->width - pd->tex_x - 1;
		if (pd->side == 1 && pd->ray_dir_y < 0)
			pd->tex_x = texture->width - pd->tex_x - 1;
		pd->step = 1.0 * texture->height / pd->line_height;
		pd->tex_pos = (pd->draw_start - mlx_data->height / 2 + pd->line_height / 2) * pd->step;
		p1.x = p0.x;
		if (pd->draw_start > 0)
		{
			p0.y = 0;
			p1.y = pd->draw_start - 1;
			drawline(&mlx_data->frame, p0, p1, (*scene).colors.ceilling);
		}
		p0.y = pd->draw_start;
		while (p0.y <= pd->draw_end)
		{
			pd->tex_y = (int)pd->tex_pos & (texture->height - 1);
			pd->tex_pos += pd->step;
			color = mlx_pixel_get(texture, texture->width - pd->tex_x, pd->tex_y);
			mlx_pixel_fill(&mlx_data->frame, p0.x, p0.y, color);
			++p0.y;
		}
		if (pd->draw_end < mlx_data->width - 1)
		{
			p0.y = pd->draw_end;
			p1.y = mlx_data->height - 1;
			drawline(&mlx_data->frame, p0, p1, (*scene).colors.floor);
		}
		++p0.x;
	}
	if (scene->render_mode == SCREENSHOT)
	{
		if (mlx_image_to_bmp_file(&mlx_data->frame, "screen.bmp"))
			exit_failure("Failed creating image \"screen.bmp\": %s\n", strerror(errno));
		exit(EXIT_SUCCESS);
	}
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, (mlx_data->frame).img, 0, 0);
	return (0);
}

void		render_scene(t_scene *scene, int mode)
{
	t_mlx_data	*mlx_data;

	mlx_data = &(*scene).mlx_data;
	(mlx_data->frame).width = mlx_data->width;
	(mlx_data->frame).height = mlx_data->height;
	(mlx_data->frame).img = mlx_new_image(mlx_data->mlx, mlx_data->width, \
		mlx_data->height);
	(mlx_data->frame).addr = mlx_get_data_addr((mlx_data->frame).img, &(mlx_data->frame).bits_per_pixel, \
		&(mlx_data->frame).line_length, &(mlx_data->frame).endian);
	if (mode == SCREENSHOT)
		render_next_frame(scene);
	mlx_data->win = mlx_new_window(mlx_data->mlx, mlx_data->width, \
		mlx_data->height, MLX_WINDOW_TITLE);
	mlx_loop_hook(mlx_data->mlx, render_next_frame, scene);
	mlx_do_key_autorepeatoff(mlx_data->mlx);
	mlx_hook(mlx_data->win, KEY_PRESS, KEY_PRESS_MASK, keypress_handler, scene);
	mlx_hook(mlx_data->win, KEY_RELEASE, KEY_RELEASE_MASK, keyrelease_handler, scene);
	mlx_hook(mlx_data->win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, winclose_handler, scene);
	mlx_loop(mlx_data->mlx);
}
