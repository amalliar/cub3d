/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_physics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 13:15:58 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/06 13:43:49 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "process_keystates.h"

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

void			process_physics(t_scene *scene)
{
	t_mlx_data			*mlx_data;
	t_player_data		*pd;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	process_player_jump(pd, mlx_data->frame_time);
	process_door_states(scene, scene->doors, scene->num_doors, \
		mlx_data->frame_time);
}
