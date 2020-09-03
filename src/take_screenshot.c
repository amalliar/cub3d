/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 05:22:23 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/03 07:35:41 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"

void		take_screenshot(t_scene *scene)
{
	t_mlx_image		*frame;

	frame = &(*scene).mlx_data.frame;
	if (!scene->render_started)
		init_frame(scene);
	render_floor_and_ceiling(scene);
	render_walls(scene);
	render_sprites(scene);
	render_hud(scene);
	frame->width = MLX_WINDOW_WIDTH;
	frame->height = MLX_WINDOW_HEIGHT;
	if (mlx_image_to_bmp_file(frame) != 0)
		exit_failure("Failed creating a screenshot: %s\n", \
		strerror(errno));
	frame->width = GAME_WINDOW_WIDTH;
	frame->height = GAME_WINDOW_HEIGHT;
}
