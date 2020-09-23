/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_physics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 13:15:58 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/23 06:07:32 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_physics.h"
#include "graphics.h"

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

static double	get_line_dist(t_line *line, double x0, double y0)
{
	return (fabs(line->a * x0 + line->b * y0 + line->c) / \
			sqrt(line->a * line->a + line->b * line->b));
}

static t_sprite *get_attack_target(t_scene *scene, t_player_data *pd)
{
	t_sprite	*sprites;
	t_sprite	*target;
	double		old_delta;
	double		new_delta;
	double		max_dist;
	int			i;

	target = NULL;
	(pd->ray).p0.x = pd->pos_x;
	(pd->ray).p0.y = pd->pos_y;
	(pd->ray).p1.x = pd->pos_x + pd->dir_x;
	(pd->ray).p1.y = pd->pos_y + pd->dir_y;
	segment_to_line(&pd->ray, &pd->line1);
	old_delta = PL_ATTACK_DELTA;
	if (pd->active_weapon->id == 0)
		max_dist = 1.5;
	else
		max_dist = pow((pd->zbuffer)[G_GAME_WINDOW_WIDTH / 2], 2);
	sprites = scene->sprites;
	i = (scene->sprite_data).num_sprites - 1;
	while (i >= 0)
	{
		if (sprites[i].dist >= max_dist)
			break ;
		if (ft_strchr(MP_ENEMIES, sprites[i].type))
		{
			new_delta = get_line_dist(&pd->line1, sprites[i].x, sprites[i].y);
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

static void		player_attack(t_scene *scene, t_player_data *pd)
{
	t_sprite	*target;
	int			dist;
	int			rand1;
	int			rand2;
	int			damage;

	target = get_attack_target(scene, pd);
	if (target == NULL)
		return ;
	dist = round(sqrt(target->dist));
	rand1 = rand() % 256;
	rand2 = rand() % 256;
	if (pd->active_weapon->id == 0)
		damage = rand2 / 16;
	else
		damage = (dist < 2) ? rand2 / 4 : rand2 / 6;
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
		if ((wpn->frame == 2) || (wpn->frame == 3 && wpn->id == 3))
			player_attack(scene, pd);
		pd->ammo -= ((wpn->frame == 2) || (wpn->frame == 3 && wpn->id == 3));
		if (pd->ammo <= 0)
		{
			pd->ammo = 0;
			wpn->state = (wpn->firing_mode == SEMI_AUTO) ? IDLE : EMPTY;
		}
	}
	else if (wpn->frame == 0)
		playSoundFromMemory((scene->sounds)[wpn->id], G_SOUNDS_VOLUME);
	else if (wpn->frame == 2)
		player_attack(scene, pd);
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
	process_enemie_states(scene);
}
