/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_mouse_motion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 00:23:08 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/10 19:55:02 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "process_key_states.h"
#include "mlx.h"
#include "graphics.h"

#define CENTER_X	GAME_WINDOW_WIDTH / 2
#define CENTER_Y	GAME_WINDOW_HEIGHT / 2

/*
** Note: we only need one function to rotate about the z-axis - the direction is
** determined by the sign of the delta.x parameter.
*/

void		process_mouse_motion(t_scene *scene)
{
	t_mlx_data	*mlx_data;
	t_point		pos;
	t_point		delta;

	if (scene->mouse_grabbing == DISABLED)
		return ;
	mlx_data = &scene->mlx_data;
	mlx_mouse_get_pos(mlx_data->win, &pos.x, &pos.y);
	delta.x = pos.x - CENTER_X;
	rotate_right(&scene->player_data, delta.x * mlx_data->frame_time * \
		PLAYER_MOUSE_SENSE);
	mlx_mouse_move(mlx_data->win, CENTER_X, CENTER_Y);
}
