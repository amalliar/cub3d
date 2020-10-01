/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 16:52:38 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/01 14:44:21 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"

void			pick_texture(t_scene *scene, t_mlx_image **texture)
{
	t_player_data	*pd;

	pd = &scene->player_data;
	if (pd->side == 0)
	{
		if (pd->ray_dir_x >= 0)
			*texture = &(scene->textures).walls.east;
		else
			*texture = &(scene->textures).walls.west;
	}
	else
	{
		if (pd->ray_dir_y >= 0)
			*texture = &(scene->textures).walls.south;
		else
			*texture = &(scene->textures).walls.north;
	}
}

void			calc_tex_x(t_scene *scene, t_mlx_image *texture)
{
	t_mlx_data		*mlx_data;
	t_player_data	*pd;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	if (pd->side == 0)
		pd->wall_x = pd->pos_y + pd->perp_wall_dist * pd->ray_dir_y;
	else
		pd->wall_x = pd->pos_x + pd->perp_wall_dist * pd->ray_dir_x;
	pd->wall_x -= floor(pd->wall_x);
	pd->tex_x = (int)(pd->wall_x * (double)texture->width);
	if (pd->side == 0 && pd->ray_dir_x > 0)
		pd->tex_x = texture->width - pd->tex_x - 1;
	if (pd->side == 1 && pd->ray_dir_y < 0)
		pd->tex_x = texture->width - pd->tex_x - 1;
	pd->step = 1.0 * texture->height / pd->line_height;
	pd->tex_pos = (pd->draw_start - mlx_data->height / 2 + \
		pd->line_height / 2) * pd->step;
}

static void		init_points(t_point *p0, t_point *p1, int x0, int y1)
{
	p0->x = x0;
	p1->x = x0;
	p0->y = 0;
	p1->y = y1;
}

void			fill_stripe(t_scene *scene, t_mlx_image *texture, int x)
{
	t_mlx_data		*mlx_data;
	t_player_data	*pd;
	t_point			p0;
	t_point			p1;
	int				color;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	init_points(&p0, &p1, x, pd->draw_start - 1);
	if (pd->draw_start > 0)
		drawverline(&mlx_data->frame, p0, p1, (scene->colors).ceilling);
	p0.y = pd->draw_start;
	while (p0.y < pd->draw_end)
	{
		pd->tex_y = (int)pd->tex_pos % texture->height;
		pd->tex_pos += pd->step;
		color = mlx_pixel_get(texture, texture->width - pd->tex_x, pd->tex_y);
		mlx_pixel_set(&mlx_data->frame, p0.x, p0.y, color);
		++p0.y;
	}
	p0.y = pd->draw_end;
	p1.y = mlx_data->height - 1;
	drawverline(&mlx_data->frame, p0, p1, (scene->colors).floor);
}
