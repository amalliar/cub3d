/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:05:07 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/16 15:22:42 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "load_scene.h"
#include "ft_string.h"
#include "ft_stdlib.h"

static void		set_resolution(t_mlx_data *mlx_data, char **words)
{
	int		wc;
	int		width;
	int		height;

	if (mlx_data->width != 0)
		exit_failure("Double initialisation of resolution");
	wc = word_count(words);
	if (wc != 3)
		exit_failure("Incorrect number of parameters for resolution: "
		"expected 3 but got %s\n", ft_itoa(wc, 10));
	if (((ft_strchr("-+", words[1][0])) ?
		!ft_strisnumeric(words[1] + 1) : !ft_strisnumeric(words[1])) || \
		((ft_strchr("-+", words[2][0])) ?
		!ft_strisnumeric(words[2] + 1) : !ft_strisnumeric(words[2])))
		exit_failure("Invalid resolution format: %s %s\n", words[2], words[3]);
	width = ft_atoi(words[1]);
	if (width <= 0 || (height = ft_atoi(words[2])) <= 0)
		exit_failure("Invalid resolution value: %s\n", \
		(width <= 0) ? ft_itoa(width, 10) : ft_itoa(height, 10));
	mlx_get_screen_size(mlx_data->mlx, &mlx_data->width, &mlx_data->height);
	if (width <= mlx_data->width && height <= mlx_data->height)
	{
		mlx_data->width = width;
		mlx_data->height = height;
	}
}

static void		set_mlx_image(t_mlx_image *mlx_image, void *img, \
					int width, int height)
{
	if (mlx_image->img != NULL)
		exit_failure("Double initialisation of texture/sprite");
	mlx_image->img = img;
	mlx_image->width = width;
	mlx_image->height = height;
	mlx_image->addr = mlx_get_data_addr(mlx_image->img, \
	&mlx_image->bits_per_pixel, &mlx_image->line_length, &mlx_image->endian);
}

static void		set_texture(t_scene *scene, char **words)
{
	int		wc;
	int		width;
	int		height;
	void	*img;

	wc = word_count(words);
	if (wc != 2)
		exit_failure("Incorrect number of parameters for texture %s: "
		"expected 2 but got %s\n", words[0], ft_itoa(wc, 10));
	if (!(img = mlx_xpm_file_to_image((*scene).mlx_data.mlx, words[1], \
		&width, &height)))
		exit_failure("Failed creating mlx image instance from file %s: %s\n", \
		words[1], strerror(errno));
	if (!ft_strcmp("NO", words[0]))
		set_mlx_image(&(*scene).textures.walls.north, img, width, height);
	else if (!ft_strcmp("SO", words[0]))
		set_mlx_image(&(*scene).textures.walls.south, img, width, height);
	else if (!ft_strcmp("WE", words[0]))
		set_mlx_image(&(*scene).textures.walls.west, img, width, height);
	else if (!ft_strcmp("EA", words[0]))
		set_mlx_image(&(*scene).textures.walls.east, img, width, height);
}

static void		set_sprite(t_scene *scene, char **words)
{
	int		wc;
	int		width;
	int		height;
	void	*img;

	wc = word_count(words);
	if (wc != 2)
		exit_failure("Incorrect number of parameters for sprite: "
		"expected 2 but got %s\n", ft_itoa(wc, 10));
	if (!(img = mlx_xpm_file_to_image((*scene).mlx_data.mlx, words[1], \
		&width, &height)))
		exit_failure("Failed creating mlx image instance from file %s: %s\n", \
		words[1], strerror(errno));
	if (!ft_strcmp("S", words[0]))
		set_mlx_image(&(*scene).textures.sprite, img, width, height);
}

int				parse_params(t_scene *scene, char *line)
{
	static int		unset_params = MANDATORY_PARAMS_COUNT;
	char			**words;

	if (ft_strisspace(line))
		return (0);
	if (!(words = ft_split(line, ' ')))
		exit_failure("%s\n", strerror(errno));
	if (ft_strstr("R", words[0]))
		set_resolution(&(*scene).mlx_data, words);
	else if (ft_strstr("S", words[0]))
		set_sprite(scene, words);
	else if (ft_strstr("F C", words[0]))
		set_color(&(*scene).colors, words);
	else if (ft_strstr("NO SO WE EA", words[0]))
		set_texture(scene, words);
	else
		exit_failure("Unknown configuration parameter: %s\n", words[0]);
	free_split_tab(words);
	--unset_params;
	return ((unset_params == 0) ? PARAMS_LOADED : 0);
}
