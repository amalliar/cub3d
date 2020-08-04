/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 21:12:41 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/03 16:14:43 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "X.h"
#include "Events.h"
#include "colors.h"
#include "graphics.h"

typedef struct	s_cursor
{
	char	*file_path;
	void	*img;
	int		img_width;
	int		img_height;
	int		x;
	int		y;
}				t_cursor;

typedef struct	s_data
{
	t_frame		*frame;
	t_cursor	*cursor;

}				t_data;

static void		set_cursor(t_data *data)
{
	int		cur_x;
	int		cur_y;

	mlx_mouse_get_pos(data->frame->win, &cur_x, &cur_y);
	if (cur_x >= 0 && cur_y >= 0 && cur_x < data->frame->win_width - data->frame->img_width && \
		cur_y < data->frame->win_height - data->frame->img_height)
	{
		mlx_mouse_hide();
		data->cursor->x = cur_x;
		data->cursor->y = cur_y;
	}
	else
		mlx_mouse_show();
}

static void		init_empty_img(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->frame->win_height)
	{
		x = 0;
		while (x < data->frame->win_width)
		{
			mlx_pixel_fill(data->frame, x, y, 0xF2F2F2);
			++x;
		}
		++y;
	}
}

static int		render_next_frame(t_data *data)
{
	set_cursor(data);
	mlx_put_image_to_window(data->frame->mlx, data->frame->win, data->frame->img, \
		0, 0);
	mlx_put_image_to_window(data->frame->mlx, data->frame->win, data->cursor->img, \
		data->cursor->x, data->cursor->y);
	return (0);
}

static int		init_data(t_data *data)
{
	if (!(data->frame = (t_frame *)malloc(sizeof(t_frame))))
		return (1);
	if (!(data->cursor = (t_cursor *)malloc(sizeof(t_cursor))))
		return (1);
	data->frame->mlx = mlx_init();
	data->frame->win_width = 1024;
	data->frame->win_height = 1024;
	data->frame->win = mlx_new_window(data->frame->mlx, data->frame->win_width, \
		data->frame->win_height, "cub3D");
	data->frame->img = mlx_new_image(data->frame->mlx, data->frame->win_width, data->frame->win_height);
	data->frame->addr = mlx_get_data_addr(data->frame->img, &data->frame->bits_per_pixel, \
		&data->frame->line_length, &data->frame->endian);
	init_empty_img(data);
	data->cursor->file_path = "./res/cursor.xpm";
	data->cursor->img = mlx_xpm_file_to_image(data->frame->mlx, data->cursor->file_path, &data->cursor->img_width, \
		&data->cursor->img_height);
	data->cursor->x = data->frame->win_width / 2;
	data->cursor->y = data->frame->win_height / 2;
	return (0);
}

static void		destroy_data(t_data *data)
{
	mlx_destroy_image(data->frame->mlx, data->frame->img);
	mlx_destroy_image(data->frame->mlx, data->cursor->img);
	free(data->frame);
	free(data->cursor);
}

int				main(void)
{
	t_data		data;

	if (init_data(&data))
		return (1);
	mlx_loop_hook(data.frame->mlx, render_next_frame, &data);
	mlx_loop(data.frame->mlx);
	destroy_data(&data);
	return (0);
}
