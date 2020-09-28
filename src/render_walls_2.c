/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 16:52:38 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/28 15:19:39 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_walls.h"

t_block			g_blocks[] =
{
	{
		DEV_N,
		DEV_S,
		DEV_E,
		DEV_W
	},
	{
		BLUE_TILE_WALL,
		BLUE_TILE_WALL,
		BLUE_TILE_WALL_DARK,
		BLUE_TILE_WALL_DARK
	},
	{
		BLUE_TILE_WALL_2,
		BLUE_TILE_WALL_2,
		BLUE_TILE_WALL_2_DARK,
		BLUE_TILE_WALL_2_DARK
	},
	{
		BLUE_TILE_DOOR,
		BLUE_TILE_DOOR,
		BLUE_TILE_DOOR_DARK,
		BLUE_TILE_DOOR_DARK
	},
	{
		BLUE_TILE_SKEL,
		BLUE_TILE_SKEL,
		BLUE_TILE_SKEL_DARK,
		BLUE_TILE_SKEL_DARK
	},
	{
		GREY_STONE_WALL,
		GREY_STONE_WALL,
		GREY_STONE_WALL_DARK,
		GREY_STONE_WALL_DARK,
	},
	{
		GREY_STONE_WALL_2,
		GREY_STONE_WALL_2,
		GREY_STONE_WALL_2_DARK,
		GREY_STONE_WALL_2_DARK,
	},
	{
		GREY_STONE_ARCH,
		GREY_STONE_ARCH,
		GREY_STONE_ARCH_DARK,
		GREY_STONE_ARCH_DARK
	},
	{
		GREY_STONE_HITLER_PICTURE,
		GREY_STONE_HITLER_PICTURE,
		GREY_STONE_HITLER_PICTURE_DARK,
		GREY_STONE_HITLER_PICTURE_DARK,
	},
	{
		GREY_STONE_BANNER,
		GREY_STONE_BANNER,
		GREY_STONE_BANNER_DARK,
		GREY_STONE_BANNER_DARK,
	},
	{
		WOODEN_WALL,
		WOODEN_WALL,
		WOODEN_WALL_DARK,
		WOODEN_WALL_DARK
	},
	{
		WOODEN_EAGLE_PICTURE,
		WOODEN_EAGLE_PICTURE,
		WOODEN_EAGLE_PICTURE_DARK,
		WOODEN_EAGLE_PICTURE_DARK
	},
	{
		WOODEN_HITLER_PICTURE,
		WOODEN_HITLER_PICTURE,
		WOODEN_HITLER_PICTURE_DARK,
		WOODEN_HITLER_PICTURE_DARK
	},
	{
		ELEVATOR_DOWN_FRONT,
		ELEVATOR_DOWN_FRONT,
		ELEVATOR_DOWN_SIDE,
		ELEVATOR_DOWN_SIDE,
	},
	{
		CYAN_METAL_DOOR,
		CYAN_METAL_DOOR,
		CYAN_METAL_DOOR_FRAME_DARK,
		CYAN_METAL_DOOR_FRAME_DARK
	},
	{
		CYAN_METAL_DOOR_FRAME,
		CYAN_METAL_DOOR_FRAME,
		CYAN_METAL_DOOR_DARK,
		CYAN_METAL_DOOR_DARK
	},
	{
		ELEVATOR_DOOR,
		ELEVATOR_DOOR,
		CYAN_METAL_DOOR_FRAME_DARK,
		CYAN_METAL_DOOR_FRAME_DARK
	},
	{
		CYAN_METAL_DOOR_FRAME,
		CYAN_METAL_DOOR_FRAME,
		ELEVATOR_DOOR_DARK,
		ELEVATOR_DOOR_DARK
	},
	{
		WOODEN_EAGLE_PICTURE,
		WOODEN_EAGLE_PICTURE,
		WOODEN_EAGLE_PICTURE_DARK,
		WOODEN_EAGLE_PICTURE_DARK
	},
	{
		GREY_STONE_HITLER_PICTURE,
		GREY_STONE_HITLER_PICTURE,
		GREY_STONE_HITLER_PICTURE_DARK,
		GREY_STONE_HITLER_PICTURE_DARK,
	},
	{
		GREY_STONE_WALL,
		GREY_STONE_WALL,
		GREY_STONE_WALL_DARK,
		GREY_STONE_WALL_DARK,
	},
	{
		GREY_STONE_WALL,
		GREY_STONE_WALL,
		GREY_STONE_WALL_DARK,
		GREY_STONE_WALL_DARK,
	},
	{
		GREY_STONE_BANNER,
		GREY_STONE_BANNER,
		GREY_STONE_BANNER_DARK,
		GREY_STONE_BANNER_DARK,
	}
};

void			check_door_hit(t_scene *scene, t_player_data *pd, \
					t_map_data *md)
{
	t_fpoint	wall;

	if (!ft_strchr(MP_DOORS, (md->map)[(int)pd->pos_y][(int)pd->pos_x]))
		return ;
	if (pd->side == 0)
	{
		wall.x = pd->map_x + (pd->ray_dir_x < 0);
		wall.y = pd->pos_y + pd->perp_wall_dist * pd->ray_dir_y;
	}
	else
	{
		wall.x = pd->pos_x + pd->perp_wall_dist * pd->ray_dir_x;
		wall.y = pd->map_y + (pd->ray_dir_y < 0);
	}
	if (wall.x >= (int)pd->pos_x && wall.x <= (int)pd->pos_x + 1 && \
		wall.y >= (int)pd->pos_y && wall.y <= (int)pd->pos_y + 1)
	{
		pd->door = get_door(scene, (int)pd->pos_x, (int)pd->pos_y);
		pd->door_hit = 1;
	}
}

static int		get_block_id(char block)
{
	return (ft_strchr(MP_BLOCKS, block) - MP_BLOCKS);
}

void			select_texture(t_player_data *pd, t_map_data *md, \
					t_mlx_image *walls, t_mlx_image **texture)
{
	int				block_id;

	if (pd->door_hit)
		block_id = get_block_id((md->map)[pd->door->y][pd->door->x]);
	else if (pd->secret_hit)
		block_id = get_block_id((md->map)[pd->secret->y][pd->secret->x]);
	else
		block_id = get_block_id((md->map)[(int)pd->map_y][(int)pd->map_x]);
	if (pd->side == 0)
	{
		if (pd->ray_dir_x >= 0)
			*texture = &walls[g_blocks[block_id].id_tex_e];
		else
			*texture = &walls[g_blocks[block_id].id_tex_w];
	}
	else
	{
		if (pd->ray_dir_y >= 0)
			*texture = &walls[g_blocks[block_id].id_tex_s];
		else
			*texture = &walls[g_blocks[block_id].id_tex_n];
	}
}

void			calc_texture_x(t_scene *scene, t_mlx_image *texture)
{
	t_mlx_data		*mlx_data;
	t_player_data	*pd;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	if (pd->side == 0)
		pd->wall_x = pd->pos_y + pd->perp_wall_dist * pd->ray_dir_y;
	else
		pd->wall_x = pd->pos_x + pd->perp_wall_dist * pd->ray_dir_x;
	if (pd->door_hit == 2)
		pd->wall_x += pd->door->s_timer;
	pd->wall_x -= floor(pd->wall_x);
	if ((pd->door_hit == 2 && ft_strchr(EW, pd->door->type) && \
		pd->ray_dir_x < 0) || (pd->door_hit == 2 && ft_strchr(NS, \
		pd->door->type) && pd->ray_dir_y > 0))
		pd->wall_x = 1.0 - pd->wall_x;
	pd->tex_x = (int)(pd->wall_x * (double)texture->width);
	if (pd->side == 0 && pd->ray_dir_x < 0)
		pd->tex_x = texture->width - pd->tex_x - 1;
	if (pd->side == 1 && pd->ray_dir_y > 0)
		pd->tex_x = texture->width - pd->tex_x - 1;
	pd->step = 1.0 * texture->height / pd->line_height;
	pd->tex_pos = (pd->draw_start - pd->pitch - \
		(pd->pos_z / pd->perp_wall_dist) - (*mlx_data).frame.height / 2 + \
		pd->line_height / 2) * pd->step;
}

void			fill_stripe(t_scene *scene, t_mlx_image *texture, int x)
{
	t_mlx_data		*mlx_data;
	t_player_data	*pd;
	int				y;
	int				color;

	mlx_data = &scene->mlx_data;
	pd = &scene->player_data;
	y = pd->draw_start;
	while (y < pd->draw_end)
	{
		pd->tex_y = (int)pd->tex_pos & (texture->height - 1);
		pd->tex_pos += pd->step;
		color = mlx_pixel_get(texture, pd->tex_x, pd->tex_y);
		mlx_pixel_set(&mlx_data->frame, x, y, color);
		++y;
	}
}
