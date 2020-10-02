/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:24:11 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 19:21:41 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_map.h"

size_t		get_cur_line_length(char *line)
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

void		gen_map_line(char *dest, char *src, int num)
{
	int		len;

	len = ft_strlen(src);
	if (num < len)
		len = num;
	ft_memcpy(dest, src, len);
	while (len < num)
	{
		dest[len] = ' ';
		++len;
	}
	dest[num] = '\0';
}

void		parse_map(t_scene *scene)
{
	int		x;
	int		y;
	char	obj;

	y = 0;
	while (y < (scene->map_data).height)
	{
		x = 0;
		while (x < (scene->map_data).width)
		{
			obj = (scene->map_data).map[y][x];
			if (!ft_strchr(DEFINED_MAP_OBJECTS, obj))
				exit_failure("Invalid map object at position [%s][%s]: %c\n", \
				ft_itoa(x + 1, 10), ft_itoa(y + 1, 10), obj);
			process_map_object(scene, x, y, obj);
			++x;
		}
		++y;
	}
	if ((scene->player_data).pos_x == -1)
		exit_failure("Map is missing player's start position\n");
}

void		process_map_object(t_scene *scene, int x, int y, char obj)
{
	if (ft_strchr(MP_INNER_OBJECTS, obj))
		check_neighbours(&scene->map_data, x, y);
	if (ft_strchr("NSEW", obj))
	{
		load_player_data(&scene->player_data, x, y, obj);
		((scene->map_data).map)[y][x] = '0';
	}
	if (obj == '2')
	{
		if (!(scene->sprites = ft_realloc(scene->sprites, \
			(scene->sprite_data).num_sprites * sizeof(t_sprite), \
			((scene->sprite_data).num_sprites + 1) * sizeof(t_sprite))))
			exit_failure("%s\n", strerror(errno));
		(scene->sprites)[(scene->sprite_data).num_sprites].x = x + 0.5;
		(scene->sprites)[(scene->sprite_data).num_sprites].y = y + 0.5;
		(scene->sprite_data).num_sprites += 1;
	}
}

void		check_neighbours(t_map_data *map_data, int mx, int my)
{
	if (mx > 0 && (map_data->map)[my][mx - 1] == ' ')
		exit_failure("Map breach detected at position [%s][%s]\n", \
		ft_itoa(mx, 10), ft_itoa(my, 10));
	if (mx < map_data->width - 1 && (map_data->map)[my][mx + 1] == ' ')
		exit_failure("Map breach detected at position [%s][%s]\n", \
		ft_itoa(mx, 10), ft_itoa(my, 10));
	if (my > 0 && (map_data->map)[my - 1][mx] == ' ')
		exit_failure("Map breach detected at position [%s][%s]\n", \
		ft_itoa(mx, 10), ft_itoa(my, 10));
	if (my < map_data->height - 1 && (map_data->map)[my + 1][mx] == ' ')
		exit_failure("Map breach detected at position [%s][%s]\n", \
		ft_itoa(mx, 10), ft_itoa(my, 10));
	if (ft_strchr(DEFINED_MAP_OBJECTS + 2, (map_data->map)[my][mx]) && \
		(mx == map_data->width - 1 || my == map_data->height - 1))
		exit_failure("Map breach detected at position [%s][%s]\n", \
		ft_itoa(mx, 10), ft_itoa(my, 10));
}
