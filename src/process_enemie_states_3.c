/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_enemie_states_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 08:50:18 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/27 05:02:56 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_enemie_states.h"

static t_fpoint		get_closest_line_point(t_line *line, double x0, double y0)
{
	t_fpoint	res;

	res.x = (line->b * (line->b * x0 - line->a * y0) - line->a * line->c) / \
		(line->a * line->a + line->b * line->b);
	res.y = (line->a * (-line->b * x0 + line->a * y0) - line->b * line->c) / \
		(line->a * line->a + line->b * line->b);
	return (res);
}

static bool			view_is_obstructed(t_scene *scene, t_sprite *en)
{
	t_player_data	*pd;
	t_fpoint		dir;
	t_point			ray;
	double			dist;

	pd = &scene->player_data;
	dir.x = (pd->pos_x - en->x) / en->dist;
	dir.y = (pd->pos_y - en->y) / en->dist;
	dist = 0;
	while (dist < en->dist)
	{
		ray.x = en->x + dist * dir.x;
		ray.y = en->y + dist * dir.y;
		if (object_collision(scene, ray.x, ray.y, 0))
			return (true);
		dist += 0.1;
	}
	return (false);
}

bool				player_out_of_scope(t_scene *scene, t_sprite *en)
{
	t_player_data	*pd;
	t_enemie_data	*ed;
	t_fpoint		inter;
	double			view_delta;
	double			max_view_delta;

	pd = &scene->player_data;
	ed = en->e_data;
	if (ed->is_tracking_player)
		adjust_view_dir(scene, en);
	(pd->ray).p0.x = en->x;
	(pd->ray).p0.y = en->y;
	(pd->ray).p1.x = en->x + ed->dir_x;
	(pd->ray).p1.y = en->y + ed->dir_y;
	segment_to_line(&pd->ray, &pd->line1);
	inter = get_closest_line_point(&pd->line1, pd->pos_x, pd->pos_y);
	if (ed->dir_x * (inter.x - en->x) + \
		ed->dir_y * (inter.y - en->y) < 0)
		return (true);
	max_view_delta = sqrt(pow(en->x - inter.x, 2) + pow(en->y - inter.y, 2));
	view_delta = \
		sqrt(pow(inter.x - pd->pos_x, 2) + pow(inter.y - pd->pos_y, 2));
	return (view_delta > max_view_delta || view_is_obstructed(scene, en) || \
		en->dist > EN_MAX_VIEWING_DIST);
}

void				check_player_presence(t_scene *scene, t_sprite *en)
{
	t_enemie_data		*ed;
	double				vperc;

	ed = en->e_data;
	if (player_out_of_scope(scene, en))
		return ;
	ed->r_timer = 0;
	if (ed->state == &g_grdshoot3)
	{
		ed->state = &g_grdshoot0;
		return ;
	}
	ed->state = &g_grdshoot0;
	vperc = 100.0 - en->dist * 3.5;
	if (vperc < 0)
		vperc = 0;
	playSoundFromMemory((scene->sounds)[SND_HALT], \
		G_SOUNDS_VOLUME * vperc / 100.0);
}
