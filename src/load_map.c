/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:18:16 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 18:23:30 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_scene.h"
#include "load_map.h"

void		load_map(t_scene *scene, int fd)
{
	char	*line;
	t_list	*lst;
	t_list	*elem;

	skip_empty_lines(fd, &line);
	if (!(elem = ft_lstnew(line)))
		exit_failure("%s\n", strerror(errno));
	lst = NULL;
	ft_lstadd_back(&lst, elem);
	build_map_lst(fd, &line, &lst);
	free(line);
	if (!((scene->map_data).map = \
		gen_map(lst, &(scene->map_data).width, &(scene->map_data).height)))
		exit_failure("%s\n", strerror(errno));
	ft_lstclear(&lst, free);
	parse_map(scene);
}

void		skip_empty_lines(int fd, char **line)
{
	int		ret;

	while ((ret = ft_get_next_line(fd, line)) > 0)
	{
		if (ft_strlen(*line) > 0)
			break ;
		free(*line);
	}
	if (ret == -1)
		exit_failure("Failed reading from a file descriptor: %s\n", \
		strerror(errno));
	if (ret == 0)
		exit_failure("Map is empty\n");
}

void		build_map_lst(int fd, char **line, t_list **lst)
{
	int		ret;
	t_list	*elem;

	while ((ret = ft_get_next_line(fd, line)) > 0 || ft_strlen(*line) > 0)
	{
		if (ft_strlen(*line) == 0)
			exit_failure("Map contains empty lines\n");
		if (!(elem = ft_lstnew(*line)))
			exit_failure("%s", strerror(errno));
		ft_lstadd_back(lst, elem);
	}
	if (ret == -1)
		exit_failure("Failed reading from a file descriptor: %s\n", \
		strerror(errno));
}

char		**gen_map(t_list *lst, int *width, int *height)
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

void		get_map_size(t_list *lst, int *width, int *height)
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
