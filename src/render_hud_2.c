/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 18:38:35 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/30 19:33:31 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_hud.h"

void		draw_crosshair(t_scene *scene)
{
	t_mlx_image		*frame;
	t_mlx_image		*cross;
	t_point			p0;

	frame = &(scene->mlx_data).frame;
	cross = scene->crosshairs + PL_CROSSHAIR;
	p0.x = frame->width / 2 - (cross->width / 2) * PL_CROSSHAIR_SCALE;
	p0.y = frame->height / 2 - (cross->height / 2) * PL_CROSSHAIR_SCALE;
	latch_image(frame, cross, p0, PL_CROSSHAIR_SCALE);
}

void		draw_fps_box(t_scene *scene)
{
	t_point		p0;
	t_point		p1;
	int			num_digits;

	if ((scene->mlx_data).frames_per_second == 0)
		num_digits = 1;
	else
		num_digits = (int)log10((scene->mlx_data).frames_per_second) + 1;
	p0.x = 0;
	p0.y = 0;
	p1.x = 17 * num_digits - 1;
	p1.y = 25;
	draw_rectangle(&(scene->mlx_data).frame, p0, p1, CLR_BLACK);
}
