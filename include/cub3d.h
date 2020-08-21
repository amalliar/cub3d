/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:02:54 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/21 23:26:09 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <stdarg.h>
# include "settings.h"

enum				e_keystates
{
	KEY_UP,
	KEY_DOWN
};

enum				e_render_modes
{
	LOOP,
	SCREENSHOT
};

typedef struct		s_mlx_image
{
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_size;
	int				endian;
	void			*img;
	char			*addr;
}					t_mlx_image;

typedef struct		s_mlx_data
{
	int				width;
	int				height;
	double			frame_time;
	void			*mlx;
	void			*win;
	t_mlx_image		frame;
}					t_mlx_data;

typedef struct		s_textures
{
	t_mlx_image		walls[NUM_WALL_TEXTURES];
	t_mlx_image		objects[NUM_OBJECT_TEXTURES];
}					t_textures;

typedef struct		s_colors
{
	int				floor;
	int				ceiling;
}					t_colors;

typedef struct		s_map_data
{
	int				width;
	int				height;
	char			**map;
}					t_map_data;

typedef struct		s_player_data
{
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	int				tex_y;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			old_dir_x;
	double			old_dir_y;
	double			plane_x;
	double			plane_y;
	double			old_plane_x;
	double			old_plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	double			move_speed;
	double			rot_speed;
	double			speed_mod;
	double			wall_x;
	double			step;
	double			tex_pos;
	double			*zbuffer;
}					t_player_data;

typedef struct		s_keystates
{
	int				kvk_ansi_w;
	int				kvk_ansi_a;
	int				kvk_ansi_s;
	int				kvk_ansi_d;
	int				kvk_leftarrow;
	int				kvk_rightarrow;
}					t_keystates;

typedef struct		s_sprite
{
	int				id_tex;
	double			x;
	double			y;
	double			dist;
}					t_sprite;

typedef struct		s_sprite_data
{
	int				num_sprites;
	int				sprite_screen_x;
	int				v_move_screen;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_x;
	int				tex_y;
	int				d;
	int				stripe;
	int				y;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
}					t_sprite_data;

typedef struct		s_scene
{
	int				render_mode;
	t_mlx_data		mlx_data;
	t_keystates		keystates;
	t_colors		colors;
	t_textures		textures;
	t_sprite		*sprites;
	t_sprite_data	sprite_data;
	t_map_data		map_data;
	t_player_data	player_data;
}					t_scene;

typedef struct		s_block
{
	int				id_tex_n;
	int				id_tex_s;
	int				id_tex_e;
	int				id_tex_w;
}					t_block;

static t_block		g_blocks[] =
{
	{0, 1, 2, 3},
	{18, 18, 19, 19},
	{20, 20, 21, 21},
	{12, 12, 13, 13},
	{16, 16, 17, 17},
};

void				load_scene(t_scene *scene, char *path);
void				render_scene(t_scene *scene, int mode);
void				render_sprites(t_scene *scene);
void				exit_failure(char *format, ...);
int					keypress_handler(int keycode, t_scene *scene);
int					keyrelease_handler(int keycode, t_scene *scene);
int					winclose_handler(t_scene *scene);

#endif
