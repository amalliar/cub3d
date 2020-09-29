/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_physics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 13:15:58 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/27 08:48:28 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_physics.h"

static void		process_player_jump(t_scene *scene)
{
	t_player_data	*pd;
	t_mlx_data		*mlx_data;

	pd = &scene->player_data;
	mlx_data = &scene->mlx_data;
	if (pd->v0 == 0)
		return ;
	pd->v0 = pd->v0 - SV_GRAVITY * mlx_data->frame_time;
	pd->pos_z += pd->v0 * mlx_data->frame_time;
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
	double				vperc;

	pd = &scene->player_data;
	if (doors[i].c_timer < 6.0)
		doors[i].c_timer += frame_time;
	if (doors[i].c_timer >= 6.0)
	{
		doors[i].state = CLOSED;
		if (door_collision(scene, pd->pos_x, pd->pos_y, MP_COLLISION_RADIUS))
			doors[i].state = OPEN;
		else
		{
			vperc = 100.0 - sqrt(pow(pd->pos_x - doors[i].x - 0.5, 2) + \
				pow(pd->pos_y - doors[i].y - 0.5, 2)) * 3.5;
			if (vperc < 0)
				vperc = 0;
			playSoundFromMemory((scene->sounds)[SND_DOOR], \
				G_SOUNDS_VOLUME * vperc / 100.0);
			doors[i].state = CLOSING;
		}
	}
}

static void		process_door_states(t_scene *scene, t_door *doors, \
					int num_doors, double frame_time)
{
	int		i;

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

void			process_physics(t_scene *scene)
{
	t_mlx_data			*mlx_data;
	t_player_data		*pd;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	process_player_jump(scene);
	process_door_states(scene, scene->doors, scene->num_doors, \
		mlx_data->frame_time);
	process_secret_states(scene);
	process_weapon_state(scene);
}
