/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:02:54 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/04 21:10:30 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define MANDATORY_PARAMS_COUNT		8
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <stdarg.h>

typedef struct		s_mlx_data
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	char			*title;
}					t_mlx_data;

typedef struct		s_mlx_image
{
	void			*img;
	int				width;
	int				height;
}					t_mlx_image;

typedef struct		s_walls
{
	t_mlx_image		north;
	t_mlx_image		south;
	t_mlx_image		west;
	t_mlx_image		east;
}					t_walls;

typedef struct		s_sprites
{
	t_mlx_image		item;	// Don't know yet what the 'item' will be.
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

typedef struct		s_scene
{
	t_mlx_data		mlx_data;
	t_textures		textures;
	t_sprites		sprites;
	t_colors		colors;
	char			**map;
}					t_scene;

void				exit_failure(char *msg, ...);

#endif
