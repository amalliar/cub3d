/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 13:04:05 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/16 13:33:47 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "graphics.h"
#include "ft_stdlib.h"
#include "ft_stdio.h"
#define U_DIV			1
#define V_DIV 			1
#define V_MOVE 			0.0

int			compar(const void *p1, const void *p2)
{
	return (((t_sprite *)p2)->dist - ((t_sprite *)p1)->dist);
}

void		render_sprites(t_scene *scene)
{
	int				i;
	t_mlx_data		*md;
	t_player_data	*pd;

	md = &scene->mlx_data;
	pd = &scene->player_data;
	i = 0;
	while (i < scene->num_sprites)
	{
		(scene->sprites)[i].dist = ((pd->pos_x - (scene->sprites)[i].x) * (pd->pos_x - (scene->sprites)[i].x) \
		+ (pd->pos_y - (scene->sprites)[i].y) * (pd->pos_y - (scene->sprites)[i].y));
		++i;
	}
	ft_qsort(scene->sprites, scene->num_sprites, sizeof(t_sprite), compar);
	i = 0;
	while (i < scene->num_sprites)
	{
		double sprite_x = (scene->sprites)[i].x - pd->pos_x;
		double sprite_y = (scene->sprites)[i].y - pd->pos_y;
		double inv_det = 1.0 / (pd->plane_x * pd->dir_y - pd->dir_x * pd->plane_y);
		double transform_x = inv_det * (pd->dir_y * sprite_x - pd->dir_x * sprite_y);
		double transform_y = inv_det * (-pd->plane_y * sprite_x + pd->plane_x * sprite_y);
		int sprite_screen_x = (int)(md->width / 2 * (1 + transform_x / transform_y));
		int v_move_screen = (int)(V_MOVE / transform_y);
		int sprite_height = ft_abs(md->height / transform_y) / V_DIV;
		int draw_start_y = -sprite_height / 2 + md->height / 2 + v_move_screen;
		if(draw_start_y < 0)
			draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + md->height / 2 + v_move_screen;
		if(draw_end_y >= md->height)
			draw_end_y = md->height - 1;
		int sprite_width = ft_abs(md->height / transform_y) / U_DIV;
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if(draw_start_x < 0)
			draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_screen_x;
		if(draw_end_x >= md->width)
			draw_end_x = md->width - 1;
		int stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * (*scene).textures.sprite.width / sprite_width) / 256;
			int y = draw_start_y;
			if (transform_y > 0 && stripe > 0 && stripe < md->width && transform_y < (pd->zbuffer)[stripe])
				while (y < draw_end_y)
				{
					int d = (y - v_move_screen) * 256 - md->height * 128 + sprite_height * 128;
					int tex_y = ((d * (*scene).textures.sprite.height) / sprite_height) / 256;
					int color = mlx_pixel_get(&(*scene).textures.sprite, tex_x, tex_y);
					if (color != 0x980088)
						mlx_pixel_fill(&md->frame, stripe, y, color);
					++y;
				}
			++stripe;
		}
		++i;
	}
}
