/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:52:19 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/15 22:56:09 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "render_walls.h"

static void		dda_init_1(t_player_data *pd, int x, int width)
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

static void		dda_init_2(t_player_data *pd)
{
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

static void		dda_run(t_scene *scene, t_player_data *pd, t_map_data *md)
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
		if (ft_strchr(MP_BLOCKS, (md->map)[(int)pd->map_y][(int)pd->map_x]))
		{
			pd->hit = 1;
			pd->door_hit = 0;
			pd->secret_hit = 0;
			if (ft_strchr(MP_SPECIAL_BLOCKS, \
				(md->map)[(int)pd->map_y][(int)pd->map_x]))
				extend_ray(scene);
		}
	}
}

static void		calc_stripe_limits(t_player_data *pd, int height)
{
	if (pd->side == 0)
		pd->perp_wall_dist = (pd->map_x - pd->pos_x + \
			(1 - pd->step_x) / 2) / pd->ray_dir_x;
	else
		pd->perp_wall_dist = (pd->map_y - pd->pos_y + \
			(1 - pd->step_y) / 2) / pd->ray_dir_y;
	pd->line_height = (int)(height / pd->perp_wall_dist);
	pd->draw_start = -pd->line_height / 2 + height / 2 + pd->pitch + \
		(pd->pos_z / pd->perp_wall_dist);
	if (pd->draw_start < 0)
		pd->draw_start = 0;
	pd->draw_end = pd->line_height / 2 + height / 2 + pd->pitch + \
		(pd->pos_z / pd->perp_wall_dist);
	if (pd->draw_end >= height)
		pd->draw_end = height - 1;
}

void			render_walls(t_scene *scene)
{
	t_mlx_data		*mlx_data;
	t_mlx_image		*texture;
	t_player_data	*pd;
	int				x;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	x = 0;
	while (x < (*mlx_data).frame.width)
	{
		dda_init_1(pd, x, (*mlx_data).frame.width);
		dda_init_2(pd);
		dda_run(scene, pd, &scene->map_data);
		calc_stripe_limits(pd, (*mlx_data).frame.height);
		check_door_hit(scene, pd, &scene->map_data);
		select_texture(scene, &texture);
		calc_texture_x(scene, texture);
		fill_stripe(scene, texture, x);
		(pd->zbuffer)[x] = pd->perp_wall_dist;
		++x;
	}
}
