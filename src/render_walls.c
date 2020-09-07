/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:52:19 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/07 17:50:57 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "ft_string.h"
#include "keypress_handler.h"
#include "graphics.h"

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

static void		init_line_segments(t_player_data *pd, t_segment *dframe1, t_segment *dframe2, \
					t_segment *door, t_segment *ray)
{
	if (pd->door->type == 'N')
	{
		(*dframe1).p0.x = pd->map_x;
		(*dframe1).p0.y = pd->map_y;
		(*dframe1).p1.x = pd->map_x;
		(*dframe1).p1.y = pd->map_y + 1.0;
		(*dframe2).p0.x = pd->map_x + 1.0;
		(*dframe2).p0.y = pd->map_y;
		(*dframe2).p1.x = pd->map_x + 1.0;
		(*dframe2).p1.y = pd->map_y + 1.0;
		(*door).p0.x = pd->map_x + 1.0 - pd->door->s_timer;
		(*door).p0.y = pd->map_y + 0.5;
		(*door).p1.x = pd->map_x + 1.0;
		(*door).p1.y = pd->map_y + 0.5;
	}
	else
	{
		(*dframe1).p0.x = pd->map_x;
		(*dframe1).p0.y = pd->map_y;
		(*dframe1).p1.x = pd->map_x + 1.0;
		(*dframe1).p1.y = pd->map_y;
		(*dframe2).p0.x = pd->map_x;
		(*dframe2).p0.y = pd->map_y + 1.0;
		(*dframe2).p1.x = pd->map_x + 1.0;
		(*dframe2).p1.y = pd->map_y + 1.0;
		(*door).p0.x = pd->map_x + 0.5;
		(*door).p0.y = pd->map_y + 1.0 - pd->door->s_timer;
		(*door).p1.x = pd->map_x + 0.5;
		(*door).p1.y = pd->map_y + 1.0;
	}
	(*ray).p0.x = pd->pos_x;
	(*ray).p0.y = pd->pos_y;
	(*ray).p1.x = pd->pos_x + pd->ray_dir_x * 1;
	(*ray).p1.y = pd->pos_y + pd->ray_dir_y * 1;
}

static void		segment_to_line(t_segment *segm, t_line *line)
{
	line->a = (*segm).p0.y - (*segm).p1.y;
	line->b = (*segm).p1.x - (*segm).p0.x;
	line->c = (*segm).p0.x * (*segm).p1.y - (*segm).p1.x * (*segm).p0.y;
}

static double	det(double a, double b, double c, double d) 
{
	return (a * d - b * c);
}

static bool 	intersect(t_line *m, t_line *n, t_fpoint *res)
{
	double		zn;

	zn = det(m->a, m->b, n->a, n->b);
	if (fabs(zn) < DBL_EPSILON)
		return (false);
	res->x = -det(m->c, m->b, n->c, n->b) / zn;
	res->y = -det(m->a, m->c, n->a, n->c) / zn;
	return (true);
}


static void		extend_ray(t_scene *scene)
{
	t_player_data	*pd;
	t_segment		dframe1;
	t_segment		dframe2;
	t_segment		door;
	t_segment		ray;
	t_line			line1;
	t_line			line2;
	t_fpoint		res;

	pd = &scene->player_data;
	pd->door = get_door(scene, (int)pd->map_x, (int)pd->map_y);
	init_line_segments(pd, &dframe1, &dframe2, &door, &ray);
	segment_to_line(&ray, &line1);
	segment_to_line(&door, &line2);
	if (intersect(&line1, &line2, &res))
	{
		if ((pd->door->type == 'N' && (res.x >= door.p0.x && res.x <= door.p1.x)) || \
			(pd->door->type == 'O' && (res.y >= door.p0.y && res.y <= door.p1.y)))
		{
			pd->map_x = res.x;
			if (pd->ray_dir_x < 0)
				pd->map_x = res.x - 1.0;
			pd->map_y = res.y;
			if (pd->ray_dir_y < 0)
				pd->map_y = res.y - 1.0;
			pd->door_hit = 2;
			if (pd->door->type == 'N')
				pd->side = 1;
			else
				pd->side = 0;
			return ;
		}
	}

	/*
	segment_to_line(&dframe1, &line2);
	if (intersect(&line1, &line2, &res)) && \
		(res.x >= dframe1.p0.x && res.x <= dframe1.p1.x))
	{
		pd->hit = 0;
		return ;
		pd->map_x = res.x;
		pd->map_y = res.y;
		pd->door_hit = 1;
		if (pd->door->type == 'N')
			pd->side = 0;
		else
			pd->side = 1;
		return ;
	}
	segment_to_line(&dframe2, &line2);
	if (intersect(&line1, &line2, &res)) && \
		(res.x >= dframe2.p0.x && res.x <= dframe2.p1.x))
	{
		pd->map_x = res.x;
		pd->map_y = res.y;
		pd->door_hit = 1;
		if (pd->door->type == 'N')
			pd->side = 0;
		else
			pd->side = 1;
		return ;
	}
	*/

	pd->hit = 0;
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
		if (ft_strchr(BLOCKS, (md->map)[(int)pd->map_y][(int)pd->map_x]))
		{
			pd->hit = 1;
			pd->door_hit = 0;
			if (ft_strchr(DOORS, (md->map)[(int)pd->map_y][(int)pd->map_x]))
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
		select_texture(scene, &texture);
		calc_texture_x(scene, texture);
		fill_stripe(scene, texture, x);
		(pd->zbuffer)[x] = pd->perp_wall_dist;
		++x;
	}
}
