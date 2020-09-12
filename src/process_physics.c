/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_physics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 13:15:58 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 19:15:33 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_key_states.h"
#include "render_scene.h"

static void		process_player_jump(t_player_data *pd, double frame_time)
{
	if (pd->v0 == 0)
		return ;
	pd->v0 = pd->v0 - SV_GRAVITY * frame_time;
	pd->pos_z += pd->v0 * frame_time;
	if (pd->pos_z < 0)
	{
		pd->pos_z = 0;
		pd->v0 = 0;
	}
}

static void		attempt_door_auto_closing(t_scene *scene, t_door *doors, \
					int i, double frame_time)
{
	t_player_data		*pd;

	pd = &scene->player_data;
	if (doors[i].c_timer < 6.0)
		doors[i].c_timer += frame_time;
	if (doors[i].c_timer >= 6.0)
	{
		doors[i].state = CLOSED;
		if (door_collision(scene, pd->pos_x, pd->pos_y))
			doors[i].state = OPEN;
		else
			doors[i].state = CLOSING;
	}
}

static void		process_door_states(t_scene *scene, t_door *doors, \
					int num_doors, double frame_time)
{
	int				i;

	i = 0;
	while (i++ < num_doors)
		if (doors[i - 1].state == CLOSING)
		{
			doors[i - 1].s_timer += frame_time;
			if (doors[i - 1].s_timer >= 1.0)
			{
				doors[i - 1].s_timer = 1.0;
				doors[i - 1].state = CLOSED;
			}
		}
		else if (doors[i - 1].state == OPENING)
		{
			doors[i - 1].s_timer -= frame_time;
			if (doors[i - 1].s_timer <= 0.0)
			{
				doors[i - 1].s_timer = 0.0;
				doors[i - 1].c_timer = 0.0;
				doors[i - 1].state = OPEN;
			}
		}
		else if (doors[i - 1].state == OPEN)
			attempt_door_auto_closing(scene, doors, i - 1, frame_time);
}

static void		process_weapon_state(t_player_data *pd)
{
	static clock_t		r_timer = 0;
	t_weapon			*wpn;

	wpn = pd->active_weapon;
	if ((wpn->state == IDLE && wpn->frame == 0) || \
		(double)(clock() - r_timer) / CLOCKS_PER_SEC < wpn->min_frame_time)
		return ;
	if (wpn->type == HITSCAN)
	{
		pd->ammo -= ((wpn->frame == 2) + (wpn->frame == 3 && wpn->id == 3));
		if (pd->ammo <= 0)
		{
			pd->ammo = 0;
			wpn->state = IDLE;
		}
	}
	if (wpn->firing_mode == FULL_AUTO && wpn->state == FIRING && \
		(wpn->frame == 2 || wpn->frame == 3))
		wpn->frame = (wpn->frame == 2) ? 3 : 2;
	else
		wpn->frame = (wpn->frame + 1) % 5;
	if (wpn->frame == 0)
		wpn->state = IDLE;
	r_timer = clock();
}

void			process_physics(t_scene *scene)
{
	t_mlx_data			*mlx_data;
	t_player_data		*pd;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	process_player_jump(pd, mlx_data->frame_time);
	process_door_states(scene, scene->doors, scene->num_doors, \
		mlx_data->frame_time);
	process_weapon_state(&scene->player_data);
}
