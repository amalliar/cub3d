/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_enemie_states_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 00:28:11 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/24 00:44:15 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_enemie_states.h"

void				drop_ammo(t_scene *scene, t_sprite *en)
{
	t_sprite		*this_sprite;
	t_sprite_data	*sd;

	sd = &scene->sprite_data;
	if (!(scene->sprites = ft_realloc(scene->sprites, \
		sd->num_sprites * sizeof(t_sprite), \
		(sd->num_sprites + 1) * sizeof(t_sprite))))
		exit_failure("%s\n", strerror(errno));
	this_sprite = scene->sprites + sd->num_sprites;
	this_sprite->x = en->x - 0.1;
	this_sprite->y = en->y;
	this_sprite->tex = (scene->textures).objects + 26;
	this_sprite->state = PLACED;
	this_sprite->type = '.';
	sd->num_sprites += 1;
}

void				adjust_view_dir(t_scene *scene, t_sprite *en)
{
	t_player_data	*pd;
	double			dist;

	pd = &scene->player_data;
	dist = sqrt(en->dist);
	en->e_data->dir_x = (pd->pos_x - en->x) / dist;
	en->e_data->dir_y = (pd->pos_y - en->y) / dist; 
}

static t_fpoint		get_closest_line_point(t_line *line, double x0, double y0)
{
	t_fpoint	res;

	res.x = (line->b * (line->b * x0 - line->a * y0) - line->a * line->c) / \
		(line->a * line->a + line->b * line->b);
	res.y = (line->a * (-line->b * x0 + line->a * y0) -line->b * line->c) / \
		(line->a * line->a + line->b * line->b);
	return (res);
}

static bool			view_is_obstructed(t_scene *scene, t_sprite *en)
{
	t_player_data	*pd;
	t_map_data		*md;
	t_point			obj;
	double			dist;
	double			max_dist;

	pd = &scene->player_data;
	md = &scene->map_data;
	max_dist = sqrt(en->dist);
	dist = 0;
	while (dist < max_dist)
	{
		obj.x = en->x + dist * en->e_data->dir_x;
		obj.y = en->y + dist * en->e_data->dir_y;
		if (object_collision(scene, obj.x, obj.y, 0.0))
			return (true);
		dist += 0.1;
	}
	return (false);
}

void			check_player_presence(t_scene *scene, t_sprite *en)
{
	t_player_data		*pd;
	t_fpoint			inter;
	double				delta;
	double				max_delta;
	double				vperc;

	pd = &scene->player_data;
	if (en->e_data->is_tracking_player)
		adjust_view_dir(scene, en);
	(pd->ray).p0.x = en->x;
	(pd->ray).p0.y = en->y;
	(pd->ray).p1.x = en->x + en->e_data->dir_x;
	(pd->ray).p1.y = en->y + en->e_data->dir_y;
	segment_to_line(&pd->ray, &pd->line1);
	inter = get_closest_line_point(&pd->line1, pd->pos_x, pd->pos_y);
	if (en->e_data->dir_x * (inter.x - en->x) + \
		en->e_data->dir_y * (inter.y - en->y) < 0)
		return ;
	max_delta = sqrt(pow(en->x - inter.x, 2) + pow(en->y - inter.y, 2));
	delta = sqrt(pow(inter.x - pd->pos_x, 2) + pow(inter.y - pd->pos_y, 2));
	if (delta > max_delta)
		return ;
	if (sqrt(en->dist) > EN_MAX_VIEWING_DISTANCE || \
		view_is_obstructed(scene, en))
		return ;
	en->e_data->r_timer = 0;
	if (en->e_data->state == &g_grdshoot3)
	{
		en->e_data->state = &g_grdshoot0;
		return ;
	}
	en->e_data->state = &g_grdshoot0;
	vperc = 100.0 - sqrt(en->dist) * 3.5;
	if (vperc < 0)
		vperc = 0;
	playSoundFromMemory((scene->sounds)[SND_HALT], G_SOUNDS_VOLUME * vperc / 100.0);
}

void			start_player_tracking(t_scene *scene, t_sprite *en)
{
	(void)scene;
	en->e_data->is_tracking_player = true;
}
