/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 14:51:10 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/24 14:13:01 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_keystates.h"
#include "ft_string.h"

int		object_collision(t_map_data *md, double pos_x, double pos_y)
{
	static double	cr = COLLISION_R;

	if (ft_strchr(COLLIDERS, (md->map)[(int)(pos_y)][(int)(pos_x + cr)]) \
	|| ft_strchr(COLLIDERS, (md->map)[(int)(pos_y)][(int)(pos_x - cr)]) \
	|| ft_strchr(COLLIDERS, (md->map)[(int)(pos_y + cr)][(int)(pos_x)]) \
	|| ft_strchr(COLLIDERS, (md->map)[(int)(pos_y - cr)][(int)(pos_x)]) \
	|| ft_strchr(COLLIDERS, (md->map)[(int)(pos_y + cr)][(int)(pos_x + cr)]) \
	|| ft_strchr(COLLIDERS, (md->map)[(int)(pos_y - cr)][(int)(pos_x + cr)]) \
	|| ft_strchr(COLLIDERS, (md->map)[(int)(pos_y + cr)][(int)(pos_x - cr)]) \
	|| ft_strchr(COLLIDERS, (md->map)[(int)(pos_y - cr)][(int)(pos_x - cr)]))
		return (1);
	return (0);
}
