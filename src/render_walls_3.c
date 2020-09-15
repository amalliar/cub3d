/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 11:07:53 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/15 17:43:42 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_walls.h"
#include "ft_string.h"

#define MP_NSSECRETS	MP_NSECRETS MP_SSECRETS
#define MP_EWSECRETS	MP_ESECRETS MP_WSECRETS

static inline void		init_fpoint(t_fpoint *p, double x, double y)
{
	p->x = x;
	p->y = y;
}

static void				init_door_segments(t_player_data *pd)
{
	if (ft_strchr(NS, pd->door->type))
	{
		init_fpoint(&(*pd).s1.p0, pd->map_x, pd->map_y);
		init_fpoint(&(*pd).s1.p1, pd->map_x, pd->map_y + 1.0);
		init_fpoint(&(*pd).s2.p0, pd->map_x + 1.0, pd->map_y);
		init_fpoint(&(*pd).s2.p1, pd->map_x + 1.0, pd->map_y + 1.0);
		init_fpoint(&(*pd).s3.p0, pd->map_x + 1.0 - pd->door->s_timer, \
			pd->map_y + 0.5);
		init_fpoint(&(*pd).s3.p1, pd->map_x + 1.0, pd->map_y + 0.5);
	}
	else
	{
		init_fpoint(&(*pd).s1.p0, pd->map_x, pd->map_y);
		init_fpoint(&(*pd).s1.p1, pd->map_x + 1.0, pd->map_y);
		init_fpoint(&(*pd).s2.p0, pd->map_x, pd->map_y + 1.0);
		init_fpoint(&(*pd).s2.p1, pd->map_x + 1.0, pd->map_y + 1.0);
		init_fpoint(&(*pd).s3.p0, pd->map_x + 0.5, \
			pd->map_y + 1.0 - pd->door->s_timer);
		init_fpoint(&(*pd).s3.p1, pd->map_x + 0.5, pd->map_y + 1.0);
	}
	init_fpoint(&(*pd).ray.p0, pd->pos_x, pd->pos_y);
	init_fpoint(&(*pd).ray.p1, pd->pos_x + pd->ray_dir_x, \
		pd->pos_y + pd->ray_dir_y);
}

static bool				door_hit(t_player_data *pd)
{
	t_fpoint		r;

	segment_to_line(&pd->ray, &pd->line1);
	segment_to_line(&pd->s3, &pd->line2);
	if (intersect(&pd->line1, &pd->line2, &r) && ((ft_strchr(NS, \
pd->door->type) && r.x >= (*pd).s3.p0.x && r.x <= (*pd).s3.p1.x) || (ft_strchr(\
EW, pd->door->type) && r.y >= (*pd).s3.p0.y && r.y <= (*pd).s3.p1.y)))
		pd->door_hit = 2;
	segment_to_line(&pd->s1, &pd->line2);
	if (!pd->door_hit && intersect(&pd->line1, &pd->line2, &r) && ((ft_strchr(\
NS, pd->door->type) && r.y >= (*pd).s1.p0.y && r.y <= (*pd).s1.p1.y) || (\
ft_strchr(EW, pd->door->type) && r.x >= (*pd).s1.p0.x && r.x <= (*pd).s1.p1.x)))
		pd->door_hit = 1;
	segment_to_line(&pd->s2, &pd->line2);
	if (!pd->door_hit && intersect(&pd->line1, &pd->line2, &r) && ((ft_strchr(\
NS, pd->door->type) && r.y >= (*pd).s2.p0.y && r.y <= (*pd).s2.p1.y) || (\
ft_strchr(EW, pd->door->type) && r.x >= (*pd).s2.p0.x && r.x <= (*pd).s2.p1.x)))
		pd->door_hit = 1;
	if (!pd->door_hit)
		return (false);
	pd->map_x = (pd->ray_dir_x > 0) ? r.x : r.x - 1.0;
	pd->map_y = (pd->ray_dir_y > 0) ? r.y : r.y - 1.0;
	pd->side = (ft_strchr(NS, pd->door->type)) ? \
		pd->door_hit == 2 : pd->door_hit != 2;
	return (true);
}

static void				init_secret_segments(t_player_data *pd)
{
	if (ft_strchr(MP_NSECRETS, pd->secret->type))
	{
		init_fpoint(&(*pd).s1.p0, pd->map_x, pd->map_y + 1.0 - pd->secret->s_timer);
		init_fpoint(&(*pd).s1.p1, pd->map_x + 1.0, pd->map_y + 1.0 - pd->secret->s_timer);
	}
	else if (ft_strchr(MP_SSECRETS, pd->secret->type))
	{
		init_fpoint(&(*pd).s1.p0, pd->map_x, pd->map_y + pd->secret->s_timer);
		init_fpoint(&(*pd).s1.p1, pd->map_x + 1.0, pd->map_y + pd->secret->s_timer);
	}
	else if (ft_strchr(MP_ESECRETS, pd->secret->type))
	{
		init_fpoint(&(*pd).s1.p0, pd->map_x + pd->secret->s_timer, pd->map_y);
		init_fpoint(&(*pd).s1.p1, pd->map_x + pd->secret->s_timer, pd->map_y + 1.0);
	}
	else if (ft_strchr(MP_WSECRETS, pd->secret->type))
	{
		init_fpoint(&(*pd).s1.p0, pd->map_x + 1.0 - pd->secret->s_timer, pd->map_y);
		init_fpoint(&(*pd).s1.p1, pd->map_x + 1.0 - pd->secret->s_timer, pd->map_y + 1.0);
	}
	init_fpoint(&(*pd).ray.p0, pd->pos_x, pd->pos_y);
	init_fpoint(&(*pd).ray.p1, pd->pos_x + pd->ray_dir_x, \
		pd->pos_y + pd->ray_dir_y);
}

static bool				secret_hit(t_player_data *pd)
{
	t_fpoint	res;

	segment_to_line(&pd->ray, &pd->line1);
	segment_to_line(&pd->s1, &pd->line2);
	if (intersect(&pd->line1, &pd->line2, &res) && \
		((ft_strchr(MP_NSSECRETS, pd->secret->type) && \
		res.x >= (*pd).s1.p0.x && res.x <= (*pd).s1.p1.x) || \
		((ft_strchr(MP_EWSECRETS, pd->secret->type)) && \
		res.y >= (*pd).s1.p0.y && res.y <= (*pd).s1.p1.y)))
	{
		pd->secret_hit = 1;
		pd->map_x = (pd->ray_dir_x > 0) ? res.x : res.x - 1.0;
		pd->map_y = (pd->ray_dir_y > 0) ? res.y : res.y - 1.0;
		pd->side = (ft_strchr(MP_NSECRETS, pd->secret->type) || \
			ft_strchr(MP_SSECRETS, pd->secret->type)) ? 1 : 0;
		return (true);
	}
	return (false);
}

void					extend_ray(t_scene *scene)
{
	t_player_data	*pd;
	t_map_data		*md;

	pd = &scene->player_data;
	md = &scene->map_data;
	if (ft_strchr(MP_DOORS, (md->map)[(int)pd->map_y][(int)pd->map_x]))
	{
		pd->door = get_door(scene, (int)pd->map_x, (int)pd->map_y);
		init_door_segments(pd);
		if (door_hit(pd))
			return ;
	}
	else if (ft_strchr(MP_SECRETS, (md->map)[(int)pd->map_y][(int)pd->map_x]))
	{
		pd->secret = get_secret(scene, (int)pd->map_x, (int)pd->map_y);
		init_secret_segments(pd);
		if (secret_hit(pd))
			return ;
	}
	pd->hit = 0;
}
