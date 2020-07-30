/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:15:08 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/30 19:44:56 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "graphics.h"

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
	int polypoints[] = {120, 250, 400, 250, 400, 350, 450, 200, 120, 250};
	drawpoly(&frame, 5, polypoints, RED);
	drawellipse(&frame, 1000, 400, 1500, 600, GREEN);
	drawcircle(&frame, 700, 700, 200, BLUE);
	mlx_put_image_to_window(mlx, mlx_win, frame.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
