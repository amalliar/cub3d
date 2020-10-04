/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 20:59:49 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/04 18:08:41 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_scene.h"
#include "load_map.h"

void	load_map(t_scene *scene, char *path)
{
	int		fd;
	t_list	*lst;

	if ((fd = open(path, O_RDONLY)) == -1)
		exit_failure("Can't open %s: %s\n", path, strerror(errno));
	lst = NULL;
	build_map_lst(fd, &lst);
	gen_map(lst, &scene->map_data);
	ft_lstclear(&lst, free);
	close(fd);
	parse_map(scene, &scene->map_data);
	init_player_stats(&scene->player_data);
	init_player_weapons(&scene->player_data, (scene->textures).hud);
}

void	build_map_lst(int fd, t_list **lst)
{
	int		ret;
	char	*line;
	t_list	*elem;

	while ((ret = ft_get_next_line(fd, &line)) > 0 || ft_strlen(line) > 0)
	{
		if (ft_strlen(line) == 0)
			exit_failure("Map contains empty lines\n");
		if (!(elem = ft_lstnew(line)))
			exit_failure("%s\n", strerror(errno));
		ft_lstadd_back(lst, elem);
	}
	if (ret == -1)
		exit_failure("Failed reading from a file descriptor: %s\n", \
		strerror(errno));
	free(line);
}

void	gen_map(t_list *lst, t_map_data *md)
{
	int		i;

	get_map_size(lst, &md->width, &md->height);
	if (!(md->map = malloc(md->height * sizeof(char *))))
		exit_failure("%s\n", strerror(errno));
	i = 0;
	while (i < md->height)
	{
		if (!((md->map)[i] = malloc(md->width + 1)))
			exit_failure("%s\n", strerror(errno));
		gen_map_line((md->map)[i], lst->content, md->width);
		lst = lst->next;
		++i;
	}
}

void	parse_map(t_scene *scene, t_map_data *md)
{
	int				x;
	int				y;
	char			obj;

	y = 0;
	while (y < md->height)
	{
		x = 0;
		while (x < md->width)
		{
			obj = (md->map)[y][x];
			if (!ft_strchr(MP_DEFINED_OBJECTS, obj))
				exit_failure("Invalid map object at position [%s][%s]: %c\n", \
				ft_itoa(x, 10), ft_itoa(y, 10), obj);
			process_map_object(scene, x, y, obj);
			++x;
		}
		++y;
	}
	if ((scene->player_data).pos_x == -1)
		exit_failure("Map is missing player's start position\n");
}

void	init_player_stats(t_player_data *pd)
{
	pd->health = 100;
	pd->lives = 3;
	pd->ammo = 8;
	pd->score = 0;
	pd->level = 1;
	pd->pitch = 0;
	pd->default_pos_x = pd->pos_x;
	pd->default_pos_y = pd->pos_y;
	pd->default_dir_x = pd->dir_x;
	pd->default_dir_y = pd->dir_y;
	pd->default_plane_x = pd->plane_x;
	pd->default_plane_y = pd->plane_y;
}
