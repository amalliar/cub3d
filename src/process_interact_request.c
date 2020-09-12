/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_interact_request.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 10:38:15 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 19:01:39 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "key_press_handler.h"

static void		switch_door_state(t_door *door)
{
	if (door->state == OPEN || door->state == OPENING)
		door->state = CLOSING;
	else if (door->state == CLOSED || door->state == CLOSING)
		door->state = OPENING;
}

t_door			*get_door(t_scene *scene, int door_x, int door_y)
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

void			process_interact_request(t_scene *scene)
{
	t_player_data	*pd;
	t_map_data		*md;
	t_point			obj;

	pd = &scene->player_data;
	md = &scene->map_data;
	obj.x = (int)(pd->pos_x + pd->dir_x * PL_MAX_INTERACT_DIST);
	obj.y = (int)(pd->pos_y + pd->dir_y * PL_MAX_INTERACT_DIST);
	if (ft_strchr(MP_DOORS, (md->map)[obj.y][obj.x]) && \
		(obj.x != (int)pd->pos_x || obj.y != (int)pd->pos_y))
		switch_door_state(get_door(scene, obj.x, obj.y));
}
