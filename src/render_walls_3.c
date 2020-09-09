/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 11:07:53 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/09 12:09:44 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_walls.h"
#include "ft_string.h"

static inline void		init_fpoint(t_fpoint *p, double x, double y)
{
	p->x = x;
	p->y = y;
}

static void				init_line_segments(t_player_data *pd)
{
	if (ft_strchr(NS, pd->door->type))
	{
		init_fpoint(&(*pd).f1.p0, pd->map_x, pd->map_y);
		init_fpoint(&(*pd).f1.p1, pd->map_x, pd->map_y + 1.0);
		init_fpoint(&(*pd).f2.p0, pd->map_x + 1.0, pd->map_y);
		init_fpoint(&(*pd).f2.p1, pd->map_x + 1.0, pd->map_y + 1.0);
		init_fpoint(&(*pd).sd.p0, pd->map_x + 1.0 - pd->door->s_timer, \
			pd->map_y + 0.5);
		init_fpoint(&(*pd).sd.p1, pd->map_x + 1.0, pd->map_y + 0.5);
	}
	else
	{
		init_fpoint(&(*pd).f1.p0, pd->map_x, pd->map_y);
		init_fpoint(&(*pd).f1.p1, pd->map_x + 1.0, pd->map_y);
		init_fpoint(&(*pd).f2.p0, pd->map_x, pd->map_y + 1.0);
		init_fpoint(&(*pd).f2.p1, pd->map_x + 1.0, pd->map_y + 1.0);
		init_fpoint(&(*pd).sd.p0, pd->map_x + 0.5, \
			pd->map_y + 1.0 - pd->door->s_timer);
		init_fpoint(&(*pd).sd.p1, pd->map_x + 0.5, pd->map_y + 1.0);
	}
	init_fpoint(&(*pd).ray.p0, pd->pos_x, pd->pos_y);
	init_fpoint(&(*pd).ray.p1, pd->pos_x + pd->ray_dir_x, \
		pd->pos_y + pd->ray_dir_y);
}

static bool				door_hit(t_player_data *pd)
{
	t_fpoint		r;

	segment_to_line(&pd->ray, &pd->line1);
	segment_to_line(&pd->sd, &pd->line2);
	if (intersect(&pd->line1, &pd->line2, &r) && ((ft_strchr(NS, \
pd->door->type) && r.x >= (*pd).sd.p0.x && r.x <= (*pd).sd.p1.x) || (ft_strchr(\
EW, pd->door->type) && r.y >= (*pd).sd.p0.y && r.y <= (*pd).sd.p1.y)))
		pd->door_hit = 2;
	segment_to_line(&pd->f1, &pd->line2);
	if (!pd->door_hit && intersect(&pd->line1, &pd->line2, &r) && ((ft_strchr(\
NS, pd->door->type) && r.y >= (*pd).f1.p0.y && r.y <= (*pd).f1.p1.y) || (\
ft_strchr(EW, pd->door->type) && r.x >= (*pd).f1.p0.x && r.x <= (*pd).f1.p1.x)))
		pd->door_hit = 1;
	segment_to_line(&pd->f2, &pd->line2);
	if (!pd->door_hit && intersect(&pd->line1, &pd->line2, &r) && ((ft_strchr(\
NS, pd->door->type) && r.y >= (*pd).f2.p0.y && r.y <= (*pd).f2.p1.y) || (\
ft_strchr(EW, pd->door->type) && r.x >= (*pd).f2.p0.x && r.x <= (*pd).f2.p1.x)))
		pd->door_hit = 1;
	if (!pd->door_hit)
		return (false);
	pd->map_x = (pd->ray_dir_x > 0) ? r.x : r.x - 1.0;
	pd->map_y = (pd->ray_dir_y > 0) ? r.y : r.y - 1.0;
	pd->side = (ft_strchr(NS, pd->door->type)) ? \
		pd->door_hit == 2 : pd->door_hit != 2;
	return (true);
}

void					extend_ray(t_scene *scene)
{
	t_player_data	*pd;

	pd = &scene->player_data;
	pd->door = get_door(scene, (int)pd->map_x, (int)pd->map_y);
	init_line_segments(pd);
	if (door_hit(pd))
		return ;
	pd->hit = 0;
}
