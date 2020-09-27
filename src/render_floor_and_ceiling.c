/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_and_ceiling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 02:03:25 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/27 09:15:13 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"

static void		calculate_floor_xy(t_mlx_image *frame, t_player_data *pd)
{
	pd->ray_dir_x0 = pd->dir_x - pd->plane_x;
	pd->ray_dir_y0 = pd->dir_y - pd->plane_y;
	pd->ray_dir_x1 = pd->dir_x + pd->plane_x;
	pd->ray_dir_y1 = pd->dir_y + pd->plane_y;
	pd->row_distance = pd->camera_z / pd->p;
	pd->floor_step_x = pd->row_distance * (pd->ray_dir_x1 - pd->ray_dir_x0) \
		/ frame->width;
	pd->floor_step_y = pd->row_distance * (pd->ray_dir_y1 - pd->ray_dir_y0) \
		/ frame->width;
	pd->floor_x = pd->pos_x + pd->row_distance * pd->ray_dir_x0;
	pd->floor_y = pd->pos_y + pd->row_distance * pd->ray_dir_y0;
}

static void		calculate_texture_xy(t_player_data *pd, t_mlx_image *tex)
{
	pd->tex_x = (int)(tex->width * \
		(pd->floor_x - pd->map_x)) & (tex->width - 1);
	pd->tex_y = (int)(tex->height * \
		(pd->floor_y - pd->map_y)) & (tex->height - 1);
}

static void		fill_hor_line(t_mlx_image *frame, t_player_data *pd, \
					t_textures *textures, int y)
{
	int		x;

	x = 0;
	while (x < frame->width)
	{
		pd->map_x = (int)pd->floor_x;
		pd->map_y = (int)pd->floor_y;
		if (pd->is_floor)
		{
			calculate_texture_xy(pd, &textures->floor);
			mlx_pixel_set(frame, x, y, mlx_pixel_get(&textures->floor, \
				pd->tex_x, pd->tex_y));
		}
		else
		{
			calculate_texture_xy(pd, &textures->ceiling);
			mlx_pixel_set(frame, x, y, mlx_pixel_get(&textures->ceiling, \
				pd->tex_x, pd->tex_y));
		}
		pd->floor_x += pd->floor_step_x;
		pd->floor_y += pd->floor_step_y;
		++x;
	}
}

void			render_floor_and_ceiling(t_scene *scene)
{
	t_mlx_image		*frame;
	t_player_data	*pd;
	int				y;

	frame = &(scene->mlx_data).frame;
	pd = &scene->player_data;
	y = 0;
	while (y < frame->height)
	{
		pd->is_floor = y > frame->height / 2 + pd->pitch;
		if (pd->is_floor)
		{
			pd->p = y - frame->height / 2 - pd->pitch;
			pd->camera_z = 0.5 * frame->height + pd->pos_z;
		}
		else
		{
			pd->p = frame->height / 2 - y + pd->pitch;
			pd->camera_z = 0.5 * frame->height - pd->pos_z;
		}
		calculate_floor_xy(frame, pd);
		fill_hor_line(frame, pd, &scene->textures, y);
		++y;
	}
}
