/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:02:54 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/14 18:32:52 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MLX_WINDOW_TITLE			"cub3D"

# define DEFINED_MAP_OBJECTS		" 102NSEW"
# define MANDATORY_PARAMS_COUNT		8
# define PARAMS_LOADED				200

# define PLAYER_FOV					80
# define PLAYER_MOVE_SPEED			0.1
# define PLAYER_ROT_SPEED			0.025

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <stdarg.h>

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
	void			*img;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	char			*addr;
}					t_mlx_image;

typedef struct		s_mlx_data
{
	void			*mlx;
	void			*win;
	t_mlx_image		frame;
	int				width;
	int				height;
}					t_mlx_data;

typedef struct		s_walls
{
	t_mlx_image		north;
	t_mlx_image		south;
	t_mlx_image		west;
	t_mlx_image		east;
}					t_walls;

typedef struct		s_sprites
{
	t_mlx_image		item;
}					t_sprites;

typedef struct		s_textures
{
	t_walls			walls;
	t_sprites		sprites;
}					t_textures;

typedef struct		s_colors
{
	unsigned int	floor;
	unsigned int	ceilling;
}					t_colors;

typedef struct		s_map_data
{
	char			**map;
	int				width;
	int				height;
}					t_map_data;

typedef struct		s_player_data
{
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
	double			wall_x;
	double			step;
	double			tex_pos;
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

typedef struct		s_scene
{
	t_mlx_data		mlx_data;
	t_textures		textures;
	t_sprites		sprites;
	t_colors		colors;
	t_map_data		map_data;
	t_player_data	player_data;
	t_keystates		keystates;
	int				render_mode;
}					t_scene;

void				exit_failure(char *format, ...);
void				load_scene(t_scene *scene, char *path);
void				render_scene(t_scene *scene, int mode);
int					keypress_handler(int keycode, t_scene *scene);
int					keyrelease_handler(int keycode, t_scene *scene);
int					winclose_handler(t_scene *scene);

#endif
