/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 02:49:23 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/01 02:55:26 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "mlx.h"

int		expose_handler(t_scene *scene)
{
	t_mlx_data		*mlx_data;

	mlx_data = &scene->mlx_data;
	scene->mouse_grabbing = ON;
	mlx_mouse_hide();
	mlx_mouse_move(mlx_data->win, mlx_data->width / 2, mlx_data->height / 2);
	return (0);
}
