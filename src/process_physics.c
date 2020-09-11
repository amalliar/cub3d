/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_physics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 13:15:58 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/11 16:15:45 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "process_key_states.h"

static void		process_player_jump(t_player_data *pd, double frame_time)
{
	if (pd->v0 == 0)
		return ;
	pd->v0 = pd->v0 - GRAVITY * frame_time;
	pd->pos_z += pd->v0 * frame_time;
	if (pd->pos_z < 0)
	{
		pd->pos_z = 0;
		pd->v0 = 0;
	}
}

static void		process_door_states(t_scene *scene, t_door *doors, \
					int num_doors, double frame_time)
{
	t_player_data	*pd;
	int				i;

	pd = &scene->player_data;
	i = 0;
	while (i < num_doors)
	{
		if (doors[i].state == CLOSING)
		{
			doors[i].s_timer += frame_time;
			if (doors[i].s_timer >= 1.0)
			{
				doors[i].s_timer = 1.0;
				doors[i].state = CLOSED;
			}
		}
		else if (doors[i].state == OPENING)
		{
			doors[i].s_timer -= frame_time;
			if (doors[i].s_timer <= 0.0)
			{
				doors[i].s_timer = 0.0;
				doors[i].c_timer = 0.0;
				doors[i].state = OPEN;
			}
		}
		else if (doors[i].state == OPEN)
		{
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
		++i;
	}
}

static void		process_weapon_state(t_player_data *pd)
{
	static clock_t		r_timer = 0;
	t_weapon			*wpn;

	wpn = pd->active_weapon;
	if ((wpn->state == IDLE && wpn->frame == 0) || \
		(double)(clock() - r_timer) / CLOCKS_PER_SEC < wpn->animation_speed / NUM_WEAPON_FRAMES)
		return ;
	if (wpn->type == HITSCAN)
	{
		pd->ammo -= (wpn->frame == 2) + (wpn->frame == 3 && wpn->id == 3);
		if (pd->ammo < 0)
			pd->ammo = 0;
		if (pd->ammo == 0)
			wpn->state = IDLE;
	}
	if (wpn->firing_mode == FULL_AUTO && wpn->state == FIRING && (wpn->frame == 2 || wpn->frame == 3))
		wpn->frame = (wpn->frame == 2) ? 3 : 2;
	else
		wpn->frame = (wpn->frame + 1) % 5;
	if (wpn->frame == 0 && wpn->firing_mode == SEMI_AUTO)
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
