/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 14:51:10 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/21 20:36:20 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_keystates.h"
#include "ft_string.h"

int		object_collision(t_map_data *md, double pos_x, double pos_y)
{
	double		angle;
	double		x;
	double		y;

	angle = 0;
	while (angle < M_PI / 2.0)
	{
		x = COLLISION_R * cos(angle);
		y = COLLISION_R * sin(angle);
		if (ft_strchr(COLLIDERS, (md->map)[(int)(pos_y + y)][(int)(pos_x - x)])\
		|| ft_strchr(COLLIDERS, (md->map)[(int)(pos_y - x)][(int)(pos_x - y)])\
		|| ft_strchr(COLLIDERS, (md->map)[(int)(pos_y - y)][(int)(pos_x + x)])\
		|| ft_strchr(COLLIDERS, (md->map)[(int)(pos_y + x)][(int)(pos_x + y)]))
			return (1);
		angle += M_PI / 180.0;
	}
	return (0);
}
