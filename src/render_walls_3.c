/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 11:07:53 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/08 11:18:25 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_walls.h"

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
	(*ray).p1.x = pd->pos_x + pd->ray_dir_x;
	(*ray).p1.y = pd->pos_y + pd->ray_dir_y;
}

static void		segment_to_line(t_segment *segm, t_line *line)
{
	line->a = (*segm).p0.y - (*segm).p1.y;
	line->b = (*segm).p1.x - (*segm).p0.x;
	line->c = (*segm).p0.x * (*segm).p1.y - (*segm).p1.x * (*segm).p0.y;
}

static inline double	det(double a, double b, double c, double d) 
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

void		extend_ray(t_scene *scene)
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
	segment_to_line(&dframe1, &line2);
	if (intersect(&line1, &line2, &res))
	{
		if ((pd->door->type == 'N' && (res.y >= dframe1.p0.y && res.y <= dframe1.p1.y)) || \
			(pd->door->type == 'O' && (res.x >= dframe1.p0.x && res.x <= dframe1.p1.x)))
		{
			pd->door_hit = 1;
			pd->map_x = res.x;
			if (pd->ray_dir_x < 0)
				pd->map_x = res.x - 1.0;
			pd->map_y = res.y;
			if (pd->ray_dir_y < 0)
				pd->map_y = res.y - 1.0;
			pd->door_hit = 1;
			if (pd->door->type == 'N')
				pd->side = 0;
			else
				pd->side = 1;
			return ;
		}
	}
	segment_to_line(&dframe2, &line2);
	if (intersect(&line1, &line2, &res))
	{
		if ((pd->door->type == 'N' && (res.y >= dframe1.p0.y && res.y <= dframe1.p1.y)) || \
			(pd->door->type == 'O' && (res.x >= dframe1.p0.x && res.x <= dframe1.p1.x)))
		{
			pd->door_hit = 1;
			pd->map_x = res.x;
			if (pd->ray_dir_x < 0)
				pd->map_x = res.x - 1.0;
			pd->map_y = res.y;
			if (pd->ray_dir_y < 0)
				pd->map_y = res.y - 1.0;
			pd->door_hit = 1;
			if (pd->door->type == 'N')
				pd->side = 0;
			else
				pd->side = 1;
			return ;
		}
	}
	pd->hit = 0;
}
