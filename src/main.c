/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:15:08 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/29 22:15:03 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "colors.h"

int		main(void)
{
	void    	*mlx;
	void    	*mlx_win;
	t_frame		frame;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "cub3D");
	frame.img = mlx_new_image(mlx, 1920, 1080);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel, \
		&frame.line_length, &frame.endian);
	frame.img_width = 1920;
	frame.img_height = 1080;
	draw_rectangle(&frame, 100, 100, 200, 200, YELLOW);
	draw_rectangle(&frame, 110, 110, 180, 180, OLIVE);
	draw_rectangle(&frame, 800, 320, 200, 400, LIME);
	draw_rectangle(&frame, 810, 330, 180, 380, GREEN);
	

	mlx_put_image_to_window(mlx, mlx_win, frame.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
