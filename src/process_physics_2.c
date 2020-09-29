/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_physics_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 06:40:19 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/27 07:10:14 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_physics.h"

static void		init_secret(char **map, t_secret *secret, int x, int y)
{
	map[y][x] = secret->type;
	secret->x = x;
	secret->y = y;
	secret->s_timer = 0;
}

static void		move_secret(t_scene *scene, int secret_id)
{
	t_map_data		*md;
	t_secret		*secret;

	md = &scene->map_data;
	secret = scene->secrets + secret_id;
	(md->map)[secret->y][secret->x] = '0';
	if (ft_strchr(MP_NSECRETS, secret->type) && \
		(md->map)[secret->y - 1][secret->x] == '0')
		init_secret(md->map, secret, secret->x, secret->y - 1);
	else if (ft_strchr(MP_SSECRETS, secret->type) && \
		(md->map)[secret->y + 1][secret->x] == '0')
		init_secret(md->map, secret, secret->x, secret->y + 1);
	else if (ft_strchr(MP_ESECRETS, secret->type) && \
		(md->map)[secret->y][secret->x + 1] == '0')
		init_secret(md->map, secret, secret->x + 1, secret->y);
	else if (ft_strchr(MP_WSECRETS, secret->type) && \
		(md->map)[secret->y][secret->x - 1] == '0')
		init_secret(md->map, secret, secret->x - 1, secret->y);
}

void			process_secret_states(t_scene *scene)
{
	t_mlx_data	*mlx_data;
	t_secret	*secrets;
	int			i;

	mlx_data = &scene->mlx_data;
	secrets = scene->secrets;
	i = 0;
	while (i < scene->num_secrets)
	{
		if (secrets[i].state == ACTIVE)
		{
			secrets[i].s_timer += mlx_data->frame_time;
			if (secrets[i].s_timer >= 1)
				move_secret(scene, i);
		}
		++i;
	}
}
