/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 22:31:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/26 04:11:16 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include "load_scene.h"

static void		skip_empty_lines(int fd, char **line)
{
	int		ret;

	while ((ret = ft_get_next_line(fd, line)) > 0)
	{
		if (!ft_strisspace(*line))
			break ;
		free(*line);
		*line = NULL;
	}
	if (ret == -1)
		exit_failure("Failed reading from a file descriptor: %s\n", \
		strerror(errno));
	if (ret == 0)
		exit_failure("Map is empty\n");
}

static void		build_map_lst(int fd, char **line, t_list **lst)
{
	int		ret;
	t_list	*elem;

	while ((ret = ft_get_next_line(fd, line)) > 0)
	{
		if (ft_strisspace(*line))
			break ;
		if (!(elem = ft_lstnew(*line)))
			exit_failure("%s", strerror(errno));
		ft_lstadd_back(lst, elem);
		*line = NULL;
	}
	if (ret == -1)
		exit_failure("Failed reading from a file descriptor: %s\n", \
		strerror(errno));
}

static void		init_player_stats(t_player_data *pd)
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

static void		load_map(t_scene *scene, char *path)
{
	int		fd;
	char	*line;
	t_list	*lst;
	t_list	*elem;

	if ((fd = open(path, O_RDONLY)) == -1)
		exit_failure("Can't open %s: %s\n", path, strerror(errno));
	line = NULL;
	skip_empty_lines(fd, &line);
	if (!(elem = ft_lstnew(line)))
		exit_failure("%s", strerror(errno));
	lst = NULL;
	line = NULL;
	ft_lstadd_back(&lst, elem);
	build_map_lst(fd, &line, &lst);
	free(line);
	if (!((scene->map_data).map = \
		gen_map(lst, &(scene->map_data).width, &(scene->map_data).height)))
		exit_failure("%s\n", strerror(errno));
	ft_lstclear(&lst, free);
	parse_map(scene);
	close(fd);
	init_player_stats(&scene->player_data);
	init_player_weapons(&scene->player_data, (scene->textures).hud);
}

void			load_scene(t_scene *scene, char *path)
{
	load_audio(scene);
	load_textures(scene);
	load_map(scene, path);
	playMusicFromMemory((scene->music)[0], G_MUSIC_VOLUME);
}
