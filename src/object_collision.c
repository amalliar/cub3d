/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 14:51:10 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 19:01:04 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "key_press_handler.h"
#include "process_key_states.h"

int			door_collision(t_scene *scene, double px, double py)
{
	t_map_data		*md;
	static double	cr = MP_COLLISION_RADIUS;

	md = &scene->map_data;
	if ((ft_strchr(MP_DOORS, (md->map)[(int)py][(int)(px + cr)]) && \
		get_door(scene, (int)(px + cr), (int)py)->state != OPEN) || \
		(ft_strchr(MP_DOORS, (md->map)[(int)py][(int)(px - cr)]) && \
		get_door(scene, (int)(px - cr), (int)py)->state != OPEN) || \
		(ft_strchr(MP_DOORS, (md->map)[(int)(py + cr)][(int)px]) && \
		get_door(scene, (int)px, (int)(py + cr))->state != OPEN) || \
		(ft_strchr(MP_DOORS, (md->map)[(int)(py - cr)][(int)px]) && \
		get_door(scene, (int)px, (int)(py - cr))->state != OPEN) || \
		(ft_strchr(MP_DOORS, (md->map)[(int)(py + cr)][(int)(px + cr)]) && \
		get_door(scene, (int)(px + cr), (int)(py + cr))->state != OPEN) || \
		(ft_strchr(MP_DOORS, (md->map)[(int)(py - cr)][(int)(px + cr)]) && \
		get_door(scene, (int)(px + cr), (int)(py - cr))->state != OPEN) || \
		(ft_strchr(MP_DOORS, (md->map)[(int)(py + cr)][(int)(px - cr)]) && \
		get_door(scene, (int)(px - cr), (int)(py + cr))->state != OPEN) || \
		(ft_strchr(MP_DOORS, (md->map)[(int)(py - cr)][(int)(px - cr)]) && \
		get_door(scene, (int)(px - cr), (int)(py - cr))->state != OPEN))
		return (1);
	return (0);
}

int			object_collision(t_scene *scene, double px, double py)
{
	t_map_data		*md;
	static double	cr = MP_COLLISION_RADIUS;

	md = &scene->map_data;
	if (ft_strchr(MP_COLLIDERS, (md->map)[(int)py][(int)(px + cr)]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)py][(int)(px - cr)]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)(py + cr)][(int)px]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)(py - cr)][(int)px]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)(py + cr)][(int)(px + cr)]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)(py - cr)][(int)(px + cr)]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)(py + cr)][(int)(px - cr)]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)(py - cr)][(int)(px - cr)]) \
	|| door_collision(scene, px, py))
		return (1);
	return (0);
}
