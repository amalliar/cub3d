/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_physics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 13:15:58 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/14 22:07:11 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_key_states.h"
#include "render_scene.h"
#include "snd.h"
#include "ft_string.h"

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
	double				vperc;

	pd = &scene->player_data;
	if (doors[i].c_timer < 6.0)
		doors[i].c_timer += frame_time;
	if (doors[i].c_timer >= 6.0)
	{
		doors[i].state = CLOSED;
		if (door_collision(scene, pd->pos_x, pd->pos_y))
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

static void		init_secret(char **map, t_secret *secret, int x, int y)
{
	map[y][x] = secret->type;
	secret->x = x;
	secret->y = y;
	secret->s_timer = 0;
}

static void		process_secret_states(t_scene *scene, t_secret *secrets, \
					int num_secrets, double frame_time)
{
	t_map_data	*md;
	int			i;

	md = &scene->map_data;
	i = 0;
	while (i < num_secrets)
	{
		if (secrets[i].state == ACTIVE)
		{
			secrets[i].s_timer += frame_time;
			if (secrets[i].s_timer >= 1)
			{
				(md->map)[secrets[i].y][secrets[i].x] = '0';
				if (ft_strchr(MP_NSECRETS, secrets[i].type) && \
					(md->map)[secrets[i].y - 1][secrets[i].x] == '0')
					init_secret(md->map, secrets + i, \
						secrets[i].x, secrets[i].y - 1);
				else if (ft_strchr(MP_SSECRETS, secrets[i].type) && \
					(md->map)[secrets[i].y + 1][secrets[i].x] == '0')
					init_secret(md->map, secrets + i, \
						secrets[i].x, secrets[i].y + 1);
				else if (ft_strchr(MP_ESECRETS, secrets[i].type) && \
					(md->map)[secrets[i].y][secrets[i].x + 1] == '0')
					init_secret(md->map, secrets + i, \
						secrets[i].x + 1, secrets[i].y);
				else if (ft_strchr(MP_WSECRETS, secrets[i].type) && \
					(md->map)[secrets[i].y][secrets[i].x - 1] == '0')
					init_secret(md->map, secrets + i, \
						secrets[i].x - 1, secrets[i].y);
			}
		}
		++i;
	}
}

static void		process_weapon_state(t_scene *scene, t_player_data *pd)
{
	static clock_t		r_timer = 0;
	t_weapon			*wpn;

	wpn = pd->active_weapon;
	if (wpn->state == EMPTY && \
		(double)(clock() - r_timer) / CLOCKS_PER_SEC >= wpn->min_frame_time)
	{
		playSoundFromMemory((scene->sounds)[SND_EMPTYCLIP], G_SOUNDS_VOLUME);
		wpn->state = IDLE;
		return ;
	}
	if ((wpn->state == IDLE && wpn->frame == 0) || \
		(double)(clock() - r_timer) / CLOCKS_PER_SEC < wpn->min_frame_time)
		return ;
	if (wpn->type == HITSCAN && pd->ammo > 0)
	{
		if (wpn->frame == 2)
			playSoundFromMemory((scene->sounds)[wpn->id], G_SOUNDS_VOLUME);
		pd->ammo -= ((wpn->frame == 2) + (wpn->frame == 3 && wpn->id == 3));
		if (pd->ammo <= 0)
		{
			pd->ammo = 0;
			wpn->state = (wpn->firing_mode == SEMI_AUTO) ? IDLE : EMPTY;
		}
	}
	else if (wpn->frame == 0)
		playSoundFromMemory((scene->sounds)[wpn->id], G_SOUNDS_VOLUME);
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
	process_secret_states(scene, scene->secrets, scene->num_secrets, \
		mlx_data->frame_time);
	process_weapon_state(scene, &scene->player_data);
}
