/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 22:31:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/11 16:15:22 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_scene.h"
#include "ft_stdio.h"
#include "ft_string.h"

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
	pd->level += 1;
	pd->pitch = 0;
}

static void		init_player_weapons(t_player_data *pd, t_mlx_image *hud)
{
	(pd->weapons)[0].id = 0;
	(pd->weapons)[0].type = MELEE;
	(pd->weapons)[0].firing_mode = SEMI_AUTO;
	(pd->weapons)[0].state = IDLE;
	(pd->weapons)[0].frame = 0;
	(pd->weapons)[0].animation_speed = 0.1;
	(pd->weapons)[0].hudpic = hud + 11;
	(pd->weapons)[0].unlocked = true;

	(pd->weapons)[1].id = 1;
	(pd->weapons)[1].type = HITSCAN;
	(pd->weapons)[1].firing_mode = SEMI_AUTO;
	(pd->weapons)[1].state = IDLE;
	(pd->weapons)[1].frame = 0;
	(pd->weapons)[1].animation_speed = 0.1;
	(pd->weapons)[1].hudpic = hud + 12;
	(pd->weapons)[1].unlocked = true;

	(pd->weapons)[2].id = 2;
	(pd->weapons)[2].type = HITSCAN;
	(pd->weapons)[2].firing_mode = FULL_AUTO;
	(pd->weapons)[2].state = IDLE;
	(pd->weapons)[2].frame = 0;
	(pd->weapons)[2].animation_speed = 0.2;
	(pd->weapons)[2].hudpic = hud + 13;
	(pd->weapons)[2].unlocked = false;

	(pd->weapons)[3].id = 3;
	(pd->weapons)[3].type = HITSCAN;
	(pd->weapons)[3].firing_mode = FULL_AUTO;
	(pd->weapons)[3].state = IDLE;
	(pd->weapons)[3].frame = 0;
	(pd->weapons)[3].animation_speed = 0.2;
	(pd->weapons)[3].hudpic = hud + 14;
	(pd->weapons)[3].unlocked = false;

	pd->active_weapon = pd->weapons + 1;
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
	if (!((*scene).map_data.map = \
		gen_map(lst, &(*scene).map_data.width, &(*scene).map_data.height)))
		exit_failure("%s\n", strerror(errno));
	ft_lstclear(&lst, free);
	parse_map(scene);
	close(fd);
	init_player_stats(&scene->player_data);
	init_player_weapons(&scene->player_data, (*scene).textures.hud);
}

void			load_scene(t_scene *scene, char *path)
{
	load_textures(scene);
	load_map(scene, path);
}
