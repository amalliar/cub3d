/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:02:54 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/06 13:34:25 by amalliar         ###   ########.fr       */
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
# include <stdbool.h>
# include "settings.h"
# include "blocks.h"

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

enum				e_states
{
	ENABLED,
	DISABLED
};

enum				e_door_states
{
	OPEN,
	CLOSED,
	OPENING,
	CLOSING
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
	int				frames_per_second;
	double			frame_time;
	void			*mlx;
	void			*win;
	t_mlx_image		frame;
}					t_mlx_data;

typedef struct		s_textures
{
	t_mlx_image		walls[NUM_WALL_TEXTURES];
	t_mlx_image		objects[NUM_OBJECT_TEXTURES];
	t_mlx_image		hud[NUM_HUD_TEXTURES];
	t_mlx_image		floor;
	t_mlx_image		ceiling;
}					t_textures;

typedef struct		s_map_data
{
	int				width;
	int				height;
	char			**map;
}					t_map_data;

typedef struct		s_player_data
{
	int				health;
	int				lives;
	int				ammo;
	int				score;
	int				level;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	int				tex_y;
	int				p;
	double			pos_x;
	double			pos_y;
	double			pos_z;
	double			map_x;
	double			map_y;
	double			dir_x;
	double			dir_y;
	double			old_dir_x;
	double			old_dir_y;
	double			plane_x;
	double			plane_y;
	double			old_plane_x;
	double			old_plane_y;
	double			camera_x;
	double			camera_z;
	double			pitch;
	double			ray_dir_x;
	double			ray_dir_x0;
	double			ray_dir_x1;
	double			ray_dir_y;
	double			ray_dir_y0;
	double			ray_dir_y1;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	double			move_speed;
	double			rot_speed;
	double			wall_x;
	double			step;
	double			tex_pos;
	double			row_distance;
	double			floor_step_x;
	double			floor_step_y;
	double			floor_x;
	double			floor_y;
	double			*zbuffer;
	double			v0;
	bool			is_floor;
}					t_player_data;

typedef struct		s_keystates
{
	int				kvk_ansi_w;
	int				kvk_ansi_a;
	int				kvk_ansi_s;
	int				kvk_ansi_d;
	int				kvk_leftarrow;
	int				kvk_rightarrow;
	int				kvk_uparrow;
	int				kvk_downarrow;
}					t_keystates;

typedef struct		s_sprite
{
	int				id_tex;
	int				state;
	double			x;
	double			y;
	double			dist;
	char			type;
}					t_sprite;

typedef struct		s_sprite_data
{
	int				num_sprites;
	int				v_move_screen;
	int				sprite_screen_x;
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
	int				id_tex;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
}					t_sprite_data;

typedef struct		s_door
{
	int				x;
	int				y;
	int				state;
	double			s_timer;
	double			c_timer;
	char			type;
}					t_door;

typedef struct		s_scene
{
	int				render_started;
	int				mouse_grabbing;
	int				num_doors;
	t_mlx_data		mlx_data;
	t_keystates		keystates;
	t_textures		textures;
	t_sprite		*sprites;
	t_sprite_data	sprite_data;
	t_map_data		map_data;
	t_door			*doors;
	t_player_data	player_data;
}					t_scene;

void				load_scene(t_scene *scene, char *path);
void				render_scene(t_scene *scene);
void				take_screenshot(t_scene *scene);
void				exit_failure(char *format, ...);

#endif
