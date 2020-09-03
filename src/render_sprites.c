/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 13:04:05 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/03 07:24:24 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "item_pickup.h"
#include "ft_stdlib.h"

#define U_DIV				1
#define V_DIV 				1
#define V_MOVE 				0.0
#define BACKGROUND			0x980088

static void		calc_sprite_dist(t_scene *scene, t_sprite *sprites)
{
	t_player_data	*pd;
	int				i;

	pd = &scene->player_data;
	i = 0;
	while (i < (*scene).sprite_data.num_sprites)
	{
		sprites[i].dist = (pow(pd->pos_x - sprites[i].x, 2) + \
			pow(pd->pos_y - sprites[i].y, 2));
		++i;
	}
}

static int		compar(const void *p1, const void *p2)
{
	return (((t_sprite *)p2)->dist - ((t_sprite *)p1)->dist);
}

static void		init_sprite_data(t_mlx_data *md, t_player_data *pd, \
					t_sprite_data *sd)
{
	sd->inv_det = 1.0 / (pd->plane_x * pd->dir_y - pd->dir_x * pd->plane_y);
	sd->transform_x = sd->inv_det * (pd->dir_y * sd->sprite_x - \
		pd->dir_x * sd->sprite_y);
	sd->transform_y = sd->inv_det * (-pd->plane_y * sd->sprite_x + \
		pd->plane_x * sd->sprite_y);
	sd->sprite_screen_x = (int)((*md).frame.width / 2 * (1 + sd->transform_x / \
		sd->transform_y));
	sd->v_move_screen = (int)(V_MOVE / sd->transform_y);
	sd->sprite_height = ft_abs((*md).frame.height / sd->transform_y) / V_DIV;
	sd->draw_start_y = -sd->sprite_height / 2 + (*md).frame.height / 2 + \
		sd->v_move_screen;
	if (sd->draw_start_y < 0)
		sd->draw_start_y = 0;
	sd->draw_end_y = sd->sprite_height / 2 + (*md).frame.height / 2 + \
		sd->v_move_screen;
	if (sd->draw_end_y >= (*md).frame.height)
		sd->draw_end_y = (*md).frame.height - 1;
	sd->sprite_width = ft_abs((*md).frame.height / sd->transform_y) / U_DIV;
	sd->draw_start_x = -sd->sprite_width / 2 + sd->sprite_screen_x;
	if (sd->draw_start_x < 0)
		sd->draw_start_x = 0;
	sd->draw_end_x = sd->sprite_width / 2 + sd->sprite_screen_x;
	if (sd->draw_end_x >= (*md).frame.width)
		sd->draw_end_x = (*md).frame.width - 1;
}

static void		draw_sprite(t_scene *scene, t_mlx_data *md, \
					t_player_data *pd, t_sprite_data *sd)
{
	int		color;

	sd->stripe = sd->draw_start_x;
	while (sd->stripe < sd->draw_end_x)
	{
		sd->tex_x = (int)(256 * (sd->stripe - (-sd->sprite_width / 2 + \
		sd->sprite_screen_x)) * (*scene).textures.objects[sd->id_tex].width \
			/ sd->sprite_width) / 256;
		sd->y = sd->draw_start_y;
		if (sd->transform_y > 0 && sd->stripe > 0 && sd->stripe < \
			(*md).frame.width && sd->transform_y < (pd->zbuffer)[sd->stripe])
			while (sd->y < sd->draw_end_y)
			{
				sd->d = (sd->y - sd->v_move_screen) * 256 - (*md).frame.height \
					* 128 + sd->sprite_height * 128;
				sd->tex_y = ((sd->d * \
	(*scene).textures.objects[sd->id_tex].height) / sd->sprite_height) / 256;
				color = mlx_pixel_get(&(*scene).textures.objects[sd->id_tex], \
					sd->tex_x, sd->tex_y);
				if (color != BACKGROUND)
					mlx_pixel_set(&md->frame, sd->stripe, sd->y, color);
				++sd->y;
			}
		++sd->stripe;
	}
}

void			render_sprites(t_scene *scene)
{
	t_sprite		*sprites;
	t_sprite_data	*sd;
	t_player_data	*pd;
	int				i;

	sprites = scene->sprites;
	sd = &scene->sprite_data;
	pd = &scene->player_data;
	calc_sprite_dist(scene, sprites);
	ft_qsort(sprites, sd->num_sprites, sizeof(t_sprite), compar);
	i = 0;
	while (i < sd->num_sprites)
	{
		if (sprites[i].state != TAKEN)
		{
			sd->sprite_x = sprites[i].x - pd->pos_x;
			sd->sprite_y = sprites[i].y - pd->pos_y;
			sd->id_tex = sprites[i].id_tex;
			init_sprite_data(&scene->mlx_data, pd, sd);
			draw_sprite(scene, &scene->mlx_data, pd, sd);
		}
		++i;
	}
}
