/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_physics_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 07:09:37 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/27 08:36:55 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_physics.h"

static double		get_line_dist(t_line *line, double x0, double y0)
{
	return (fabs(line->a * x0 + line->b * y0 + line->c) / \
			sqrt(line->a * line->a + line->b * line->b));
}

static t_sprite		*find_target(t_scene *scene, t_sprite *sprites, \
						double max_dist)
{
	t_sprite	*target;
	double		old_delta;
	double		new_delta;
	int			i;

	old_delta = PL_ATTACK_DELTA;
	target = NULL;
	i = (scene->sprite_data).num_sprites - 1;
	while (i >= 0)
	{
		if (sprites[i].dist >= max_dist)
			return (target);
		if (ft_strchr(MP_ENEMIES, sprites[i].type))
		{
			new_delta = get_line_dist(&(scene->player_data).line1, \
				sprites[i].x, sprites[i].y);
			if (new_delta < old_delta && sprites[i].e_data->is_alive)
			{
				target = sprites + i;
				old_delta = new_delta;
			}
		}
		--i;
	}
	return (target);
}

static t_sprite		*get_attack_target(t_scene *scene)
{
	t_player_data	*pd;
	double			max_dist;

	pd = &scene->player_data;
	(pd->ray).p0.x = pd->pos_x;
	(pd->ray).p0.y = pd->pos_y;
	(pd->ray).p1.x = pd->pos_x + pd->dir_x;
	(pd->ray).p1.y = pd->pos_y + pd->dir_y;
	segment_to_line(&pd->ray, &pd->line1);
	if (pd->active_weapon->id == 0)
		max_dist = 1.5;
	else
		max_dist = (pd->zbuffer)[G_GAME_WINDOW_WIDTH / 2];
	return (find_target(scene, scene->sprites, max_dist));
}

void				player_attack(t_scene *scene)
{
	t_sprite	*target;
	int			rand1;
	int			rand2;
	int			damage;

	target = get_attack_target(scene);
	if (target == NULL)
		return ;
	rand1 = rand() % 256;
	rand2 = rand() % 256;
	if ((scene->player_data).active_weapon->id == 0)
		damage = rand2 / 16;
	else
		damage = (round(target->dist) <= 2) ? rand2 / 4 : rand2 / 6;
	target->e_data->health -= damage;
	if (target->e_data->health > 0)
		target->e_data->state = &g_grdpain;
	else
	{
		target->e_data->is_alive = false;
		target->e_data->state = &g_grddie0;
	}
	target->e_data->r_timer = 0;
}
