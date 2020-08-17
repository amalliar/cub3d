/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 22:31:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/17 16:07:15 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_scene.h"
#include "ft_stdio.h"
#include "ft_string.h"

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
		exit_failure("Failed reading from a file descriptor: %s\n", \
		strerror(errno));
	else if (ret == 0)
		exit_failure("%s", \
		"Scene file is missing mandatory configuration parameters\n");
}

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

static void		load_map(t_scene *scene, int fd)
{
	char	*line;
	t_list	*lst;
	t_list	*elem;

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
