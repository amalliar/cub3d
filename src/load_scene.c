/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 22:31:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/14 14:50:25 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "colors.h"
#include "ft_stdio.h"
#include "ft_ctype.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "ft_list.h"

static void		free_split_tab(char **words)
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

	if (mlx_data->width != 0)
		exit_failure("Double initialisation of resolution");
	wc = word_count(words);
	if (wc != 3)
		exit_failure("Incorrect number of parameters for resolution: expected 3 but got %s\n", ft_itoa(wc, 10));
	if ((ft_strchr("-+", words[1][0])) ?
		!ft_strisnumeric(words[1] + 1) : !ft_strisnumeric(words[1]) || \
		(ft_strchr("-+", words[2][0])) ?
		!ft_strisnumeric(words[2] + 1) : !ft_strisnumeric(words[2]))
		exit_failure("Invalid resolution format: %s %s\n", words[2], words[3]);
	width = ft_atoi(words[1]);
	height = ft_atoi(words[2]);
	if (width <= 0 || height <= 0)
		exit_failure("Invalid resolution value: %s\n", (width <= 0) ? ft_itoa(width, 10) : ft_itoa(height, 10));
	mlx_get_screen_size(mlx_data->mlx, &mlx_data->width, &mlx_data->height);
	if (width <= mlx_data->width && height <= mlx_data->height)
	{
		mlx_data->width = width;
		mlx_data->height = height;
	} }

static void		set_mlx_image(t_mlx_image *mlx_image, void *img, int width, int height)
{
	if (mlx_image->img != NULL)
		exit_failure("Double initialisation of texture/sprite");
	mlx_image->img = img;
	mlx_image->width = width;
	mlx_image->height = height;
	mlx_image->addr = mlx_get_data_addr(mlx_image->img, &mlx_image->bits_per_pixel, \
		&mlx_image->line_length, &mlx_image->endian);
}

static void		set_texture(t_scene *scene, char **words)
{
	int		wc;
	int		width;
	int		height;
	void	*img;

	wc = word_count(words);
	if (wc != 2)
		exit_failure("Incorrect number of parameters for texture %s: expected 2 but got %s\n", words[0], ft_itoa(wc, 10));
	if (!(img = mlx_xpm_file_to_image((*scene).mlx_data.mlx, words[1], &width, &height)))
		exit_failure("Failed creating mlx image instance from file %s: %s\n", words[1], strerror(errno));
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
		exit_failure("Incorrect number of parameters for sprite: expected 2 but got %s\n", ft_itoa(wc, 10));
	if (!(img = mlx_xpm_file_to_image((*scene).mlx_data.mlx, words[1], &width, &height)))
		exit_failure("Failed creating mlx image instance from file %s: %s\n", words[1], strerror(errno));
	if (!ft_strcmp("S", words[0]))
		set_mlx_image(&(*scene).sprites.item, img, width, height);
}

static void		set_color(t_colors *colors, char **words)
{
	int		wc;
	int		r;
	int		g;
	int		b;
	char	**rgb_values;

	wc = word_count(words);
	if (wc != 2)
		exit_failure("Incorrect number of parameters for color: expected 2 but got %s\n", ft_itoa(wc, 10));
	if (!(rgb_values = ft_split(words[1], ',')))
		exit_failure("%s\n", strerror(errno));
	wc = word_count(rgb_values);
	if (wc != 3)
		exit_failure("Invalid R,G,B format: %s\n", words[1]);
	if ((ft_strchr("-+", rgb_values[0][0])) ?
		!ft_strisnumeric(rgb_values[0] + 1) : !ft_strisnumeric(rgb_values[0]) || \
		(ft_strchr("-+", rgb_values[1][0])) ?
		!ft_strisnumeric(rgb_values[1] + 1) : !ft_strisnumeric(rgb_values[1]) || \
		(ft_strchr("-+", rgb_values[2][0])) ?
		!ft_strisnumeric(rgb_values[2] + 1) : !ft_strisnumeric(rgb_values[2]))
		exit_failure("Invalid R,G,B format: %s\n", words[1]);
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	free_split_tab(rgb_values);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_failure("Invalid R,G,B value: %s\n", words[1]);
	if (!ft_strcmp("F", words[0]))
		colors->floor = create_color(0, r, g, b);
	else if (!ft_strcmp("C", words[0]))
		colors->ceilling = create_color(0, r, g, b);
}

static int		parse_params(t_scene *scene, char *line)
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
		exit_failure("Scene file is missing mandatory configuration parameters\n");
}

static size_t	get_cur_line_length(char *line)
{
	int		len;

	len = ft_strlen(line);
	while (len > 0)
	{
		if (!ft_isspace(line[len - 1]))
			break ;
		--len;
	}
	return (len);
}

static void		get_map_size(t_list *lst, int *width, int *height)
{
	int		cur_line_length;

	*width = 0;
	*height = 0;
	while (lst)
	{
		++*height;
		cur_line_length = get_cur_line_length(lst->content);
		if (cur_line_length > *width)
			*width = cur_line_length;
		lst = lst->next;
	}
}

static void		gen_map_line(char *dest, char *src, int num)
{
	int		len;

	len = ft_strlen(src);
	if (num < len)
		len = num;
	ft_memcpy(dest, src, len);
	while(len < num)
	{
		dest[len] = ' ';
		++len;
	}
	dest[num] = '\0';
}

static char		**gen_map(t_list *lst, int *width, int *height)
{
	int		i;
	char	**map;

	get_map_size(lst, width, height);
	if (!(map = malloc(*height * sizeof(char *))))
		exit_failure("%s\n", strerror(errno));
	i = 0;
	while (i < *height)
	{
		if (!(map[i] = malloc(*width + 1)))
			exit_failure("%s\n", strerror(errno));
		gen_map_line(map[i], lst->content, *width);
		lst = lst->next;
		++i;
	}
	return (map);
}

static void		check_neighbours(t_map_data *map_data, int mx, int my)
{
	if (mx > 0 && (map_data->map)[my][mx - 1] == ' ')
		exit_failure("Map breach detected at position [%s][%s]\n", ft_itoa(mx, 10), ft_itoa(my, 10));
	if (mx < map_data->width - 1 && (map_data->map)[my][mx + 1] == ' ')
		exit_failure("Map breach detected at position [%s][%s]\n", ft_itoa(mx, 10), ft_itoa(my, 10));
	if (my > 0 && (map_data->map)[my - 1][mx] == ' ')
		exit_failure("Map breach detected at position [%s][%s]\n", ft_itoa(mx, 10), ft_itoa(my, 10));
	if (my < map_data->height - 1 && (map_data->map)[my + 1][mx] == ' ')
		exit_failure("Map breach detected at position [%s][%s]\n", ft_itoa(mx, 10), ft_itoa(my, 10));
	if (ft_strchr(DEFINED_MAP_OBJECTS + 2, (map_data->map)[my][mx]) && \
		(mx == map_data->width - 1 || my == map_data->height - 1))
		exit_failure("Map breach detected at position [%s][%s]\n", ft_itoa(mx, 10), ft_itoa(my, 10));
}

static void		load_player_data(t_player_data *player_data, int x, int y, char obj)
{
	if (player_data->pos_x != -1)
		exit_failure("Double initialisation of player's start position\n");
	player_data->pos_x = x;
	player_data->pos_y = y;
	if (obj == 'N')
	{
		player_data->dir_x = 0;
		player_data->dir_y = -1;
		player_data->plane_x = tan(PLAYER_FOV * M_PI / 360);
		player_data->plane_y = 0;
	}
	else if (obj == 'S')
	{
		player_data->dir_x = 0;
		player_data->dir_y = 1;
		player_data->plane_x = -tan(PLAYER_FOV * M_PI / 360);
		player_data->plane_y = 0;

	}
	else if (obj == 'E')
	{
		player_data->dir_x = 1;
		player_data->dir_y = 0;
		player_data->plane_x = 0;
		player_data->plane_y = tan(PLAYER_FOV * M_PI / 360);
	}
	else if (obj == 'W')
	{
		player_data->dir_x = -1;
		player_data->dir_y = 0;
		player_data->plane_x = 0;
		player_data->plane_y = -tan(PLAYER_FOV * M_PI / 360);
	}
}

static void		process_map_object(t_scene *scene, int x, int y, char obj)
{
	if (!ft_strchr(" 1", obj))
		check_neighbours(&(*scene).map_data, x, y);
	if (ft_strchr("NSEW", obj))
	{
		load_player_data(&(*scene).player_data, x, y, obj);
		((*scene).map_data.map)[y][x] = '0';
	}
}

static void		parse_map(t_scene *scene)
{
	int		x;
	int		y;
	char	obj;

	y = 0;
	while (y < (*scene).map_data.height)
	{
		x = 0;
		while (x < (*scene).map_data.width)
		{
			obj = (*scene).map_data.map[y][x];
			if (!ft_strchr(DEFINED_MAP_OBJECTS, obj))
				exit_failure("Invalid map object at position [%s][%s]: %c\n", ft_itoa(x, 10), ft_itoa(y, 10), obj);
			process_map_object(scene, x, y, obj);
			++x;
		}
		++y;
	}
	if ((*scene).player_data.pos_x == -1)
		exit_failure("Map is missing player's start position\n");
}

static void		load_map(t_scene *scene, int fd)
{
	int		ret;
	char	*line;
	t_list	*lst;
	t_list	*elem;

	line = NULL;
	while ((ret = ft_get_next_line(fd, &line)) > 0)
	{
		if (!ft_strisspace(line))
			break ;
		free(line);
		line = NULL;
	}
	if (ret == -1)
		exit_failure("Failed reading from a file descriptor: %s\n", strerror(errno));
	if (ret == 0)
		exit_failure("Map is empty\n");
	if (!(elem = ft_lstnew(line)))
		exit_failure("%s", strerror(errno));
	lst = NULL;
	line = NULL;
	ft_lstadd_back(&lst, elem);
	while ((ret = ft_get_next_line(fd, &line)) > 0)
	{
		if (ft_strisspace(line))
			break ;
		if (!(elem = ft_lstnew(line)))
			exit_failure("%s", strerror(errno));
		ft_lstadd_back(&lst, elem);
		line = NULL;
	}
	if (ret == -1)
		exit_failure("Failed reading from a file descriptor: %s\n", strerror(errno));
	free(line);
	if (!((*scene).map_data.map = gen_map(lst, &(*scene).map_data.width, &(*scene).map_data.height)))
		exit_failure("%s\n", strerror(errno));
	ft_lstclear(&lst, free);
	parse_map(scene);
}

void			load_scene(t_scene *scene, char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		exit_failure("Can't open %s: %s\n", path, strerror(errno));
	load_params(scene, fd);
	load_map(scene, fd);
	close(fd);
}
