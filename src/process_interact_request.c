/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_interact_request.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 10:38:15 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/27 12:29:46 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "key_press_handler.h"
#include "snd.h"

static t_point		calculate_ray_position(t_player_data *pd, double dist)
{
	t_point		ray;

	ray.x = (int)(pd->pos_x + pd->dir_x * dist);
	ray.y = (int)(pd->pos_y + pd->dir_y * dist);
	return (ray);
}

static void			switch_door_state(t_scene *scene, t_door *door)
{
	if (door->state == OPEN || door->state == OPENING)
		door->state = CLOSING;
	else if (door->state == CLOSED || door->state == CLOSING)
		door->state = OPENING;
	playSoundFromMemory((scene->sounds)[SND_DOOR], G_SOUNDS_VOLUME);
}

t_door				*get_door(t_scene *scene, int door_x, int door_y)
{
	int		i;

	i = 0;
	while (i < scene->num_doors)
	{
		if ((scene->doors)[i].x == door_x && (scene->doors)[i].y == door_y)
			return (scene->doors + i);
		++i;
	}
	exit_failure("Can't find door object x: %s, y: %s\n", \
		ft_itoa(door_x, 10), ft_itoa(door_y, 10));
	return (NULL);
}

t_secret			*get_secret(t_scene *scene, int secr_x, int secr_y)
{
	int		i;

	i = 0;
	while (i < scene->num_secrets)
	{
		if ((scene->secrets)[i].x == secr_x && (scene->secrets)[i].y == secr_y)
			return (scene->secrets + i);
		++i;
	}
	exit_failure("Can't find secret object x: %s, y: %s\n", \
		ft_itoa(secr_x, 10), ft_itoa(secr_y, 10));
	return (NULL);
}

void				process_interact_request(t_scene *scene, \
						t_player_data *pd, t_map_data *md)
{
	t_point			ray;
	t_secret		*secret;
	double			dist;

	dist = 0;
	while (dist <= PL_MAX_INTERACT_DIST)
	{
		ray = calculate_ray_position(pd, dist);
		if (ft_strchr(MP_DOORS, (md->map)[ray.y][ray.x]) && \
			(ray.x != (int)pd->pos_x || ray.y != (int)pd->pos_y))
			return ((void)switch_door_state(scene, \
				get_door(scene, ray.x, ray.y)));
		else if (ft_strchr(MP_SECRETS, (md->map)[ray.y][ray.x]))
		{
			secret = get_secret(scene, ray.x, ray.y);
			if (secret->state == IDLE)
				playSoundFromMemory((scene->sounds)[SND_SECRET], \
					G_SOUNDS_VOLUME);
			secret->state = ACTIVE;
			return ;
		}
		else if (ft_strchr(MP_COLLIDERS, (md->map)[ray.y][ray.x]))
			return ;
		dist += 0.1;
	}
}
