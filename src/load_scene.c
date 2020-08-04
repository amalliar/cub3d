/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 22:31:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/04 18:31:47 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_stdio.h"
#include "ft_list.h"

static void		free_words(char **words)
{
	int		i;

	i = 0;
	while (words[i] != NULL)
	{
		free(words[i]);
		++i;
	}
	free(words);
}

static int		word_count(char **words)
{
	int		i;

	i = 0;
	while (words[i] != NULL)
		++i;
	return (i);
}

static void		set_resolution(t_mlx_data *mlx_data, char **words)
{
	int		wc;
	int		width;
	int		height;

	wc = word_count(words);
	if (wc != 3)
		exit_failure("Incorrect number of parameters for resolution: expected 3 but got %s\n", ft_itoa(wc));
	if (!ft_strisnumeric(words[2]) || !ft_strisnumeric(words[3]))
		exit_failure("Invalid resolution format: %s %s\n", words[2], words[3]);
	width = ft_atoi(words[1]);
	height = ft_atoi(words[2]);
	if (width <= 0 || height <= 0)
		exit_failure("Invalid resolution value: %s\n", (width <= 0) ? ft_itoa(width) : ft_itoa(height));
	mlx_data->width = width;
	mlx_data->height = height;
}

static void		set_mlx_image(t_mlx_image *mlx_image, void *img, int width, int height)
{
	mlx_image->img = img;
	mlx_image->width = width;
	mlx_image->height = height;
}

static void		set_texture(t_scene *scene, char **words)
{
	int		wc;
	int		width;
	int		height;
	void	*img;

	wc = word_count(words);
	if (wc != 2)
		exit_failure("Incorrect number of parameters for texture: expected 2 but got %s\n", ft_itoa(wc));
	img = mlx_xpm_file_to_image((*scene).mlx_data.mlx, words[1], &width, &height);
	if (img == NULL)
		exit_failure("Failed creating mlx image instance from file %s: %s\n", words[1], strerror(errno));
	if (!ft_strcmp("NO", words[0]))
		set_mlx_image(&(*scene).textures.walls.north, img, width, height);
	else if (!ft_strcmp("SO", words[0]))
		set_mlx_image(&(*scene).textures.walls.south, img, width, height);
	else if (!ft_strcmp("WE", words[0]))
		set_mlx_image(&(*scene).textures.walls.west, img, width, height);
	else if (!ft_strcmp("EA", words[0]))
		set_mlx_image(&(*scene).textures.walls.east, img, width, height);
	else
		exit_error("Unknown configuration parameter: %s", words[0]);
}

static void		set_sprite(t_scene *scene, char **words)
{
	int		wc;
	int		width;
	int		height;
	void	*img;

	wc = word_count(words);
	if (wc != 2)
		exit_failure("Incorrect number of parameters for sprite: expected 2 but got %s\n", ft_itoa(wc));
	img = mlx_xpm_file_to_image((*scene).mlx_data.mlx, words[1], &width, &height);
	if (img == NULL)
		exit_failure("Failed creating mlx image instance from file %s: %s\n", words[1], strerror(errno));
	if (!ft_strcmp("S", words[0]))
		set_mlx_image(&(*scene).sprites.item, img, width, height);
	else
		exit_error("Unknown configuration parameter: %s", words[0]);
}

static int		strisrgb(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' || *str <= '9' || *str == ','))
			return (0);
		++str;
	}
	return (1);
}

static void		set_color(t_colors *colors, char **words)
{
	int		wc;
	int		r;
	int		g;
	int		b;
	char	*nex_sep;

	wc = word_count(words);
	if (wc != 2)
		exit_failure("Incorrect number of parameters for color: expected 2 but got %s\n", ft_itoa(wc));
	if (!strisrgb(words[1]))
		exit_failure("Invalid R,G,B format: %s\n", words[1]);
	r = ft_atoi(words[1]);
	if (!(next_sep = ft_strchr(words[1], ',')) || *(next_sep + 1) == '\0')
		exit_failure("Invalid R,G,B format: %s\n", words[1]);
	g = ft_atoi(next_sep + 1);
	if (!(next_sep = ft_strchr(next_sep + 1, ',')) || *(next_sep + 1) == '\0')
		exit_failure("Invalid R,G,B format: %s\n", words[1]);
	b = ft_atoi(next_sep + 1);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_failure("Invalid R,G,B value: %s\n", words[1]);
	if (!ft_strcmp("F", words[0]))
		colors->floor = create_color(r, g, b);
	else if (!ft_strcmp("C", words[0]))
		colors->ceilling = create_color(r, g, b);
	else
		exit_error("Unknown configuration parameter: %s", words[0]);
}

static int		parse_params(t_scene *scene, char *line)
{
	static int		unset_params = MANDATORY_PARAMS_COUNT;
	int				ret;
	char			**words;

	if (!(words = ft_split(line, ' ')))
		exit_failure("%s\n", strerror(errno));
	if (words[0][0] == '\0')
	{
		free_words(words);
		return (0);
	}
	if (ft_strnstr("R", words[0], sizeof("R") - 1))
		set_resolution(&(*scene).mlx_data, words);
	else if (ft_strnstr("NO SO WE EA", words[0], sizeof("NO SO WE EA") - 1))
		set_texture(scene, words);
	else if (ft_strnstr("S", words[0], sizeof("S") - 1))
		set_sprite(scene, words);
	else if (ft_strnstr("F C", words[0], sizeof("F C") - 1))
		set_color(&(*scene).colors, words);
	else
		exit_error("Unknown configuration parameter: %s", words[0]);
	free_words(words);
	--unset_params;
	return ((unset_params == 0) ? PARAMS_LOADED : 0);
}

static void		load_params(t_scene *scene, int fd)
{
	int		ret;
	char	*line;

	line = NULL;
	while ((ret = ft_get_next_line(fd, &line)) > 0)
	{
		ret = parse_params(scene, line);
		free(line);
		line = NULL;
		if (ret == PARAMS_LOADED)
			break ;
	}
	if (ret == -1) 
		exit_failure("Failed reading from a file descriptor: %s\n", strerror(errno));
	else if (ret == 0)
		exit_failure("Scene file is missing mandatory configuration parameters.\n");
}

static void		load_map(t_scene *scene, int fd)
{
	int		ret;
	char	*line;
	t_list	*lst;
	t_list	*elem;

	line = NULL;
	lst = NULL;
	while ((ret = ft_get_next_line(fd, &line)) > 0)
	{
		if (!(elem = ft_lstnew(line)))
			exit_failure("%s", strerror(errno));
		ft_lstadd_back(&lst, elem);
		line = NULL;
	}
	if (ret == -1)
		exit_failure("Failed reading from a file descriptor: %s\n", strerror(errno));
}

void			load_scene(t_scene *scene, char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		exit_failure("Can't open %s: %s\n", path, strerror(errno));
	load_params(scene, fd);
	load_map(scene, fd);
}
