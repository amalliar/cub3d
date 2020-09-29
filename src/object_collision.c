/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 14:51:10 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 05:52:02 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "key_press_handler.h"
#include "process_key_states.h"

int			block_collision(t_scene *scene, double px, double py, double cr)
{
	t_map_data		*md;

	md = &scene->map_data;
	if (ft_strchr(MP_COLLIDERS, (md->map)[(int)py][(int)(px + cr)]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)py][(int)(px - cr)]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)(py + cr)][(int)px]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)(py - cr)][(int)px]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)(py + cr)][(int)(px + cr)]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)(py - cr)][(int)(px + cr)]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)(py + cr)][(int)(px - cr)]) \
	|| ft_strchr(MP_COLLIDERS, (md->map)[(int)(py - cr)][(int)(px - cr)]))
		return (1);
	return (0);
}

int			door_collision(t_scene *scene, double px, double py, double cr)
{
	t_map_data		*md;

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

int			enemie_collision(t_scene *scene, double px, double py, double cr)
{
	t_sprite	*sprites;
	int			i;

	if (cr > 0)
		cr = 2.0 * MP_COLLISION_RADIUS;
	sprites = scene->sprites;
	i = (scene->sprite_data).num_sprites - 1;
	while (i >= 0 && sprites[i].dist <= cr + 0.5)
	{
		if (ft_strchr(MP_ENEMIES, sprites[i].type) && \
			sprites[i].e_data->is_alive && \
			sqrt(pow(sprites[i].x - px, 2) + pow(sprites[i].y - py, 2)) <= cr)
		{
			sprites[i].e_data->is_tracking_player = true;
			return (1);
		}
		--i;
	}
	return (0);
}

int			object_collision(t_scene *scene, double px, double py, double cr)
{
	return (block_collision(scene, px, py, cr) || \
			door_collision(scene, px, py, cr) || \
			enemie_collision(scene, px, py, cr));
}
