/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:44:11 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 19:02:34 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "load_scene.h"

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
	while (len < num)
	{
		dest[len] = ' ';
		++len;
	}
	dest[num] = '\0';
}

char			**gen_map(t_list *lst, int *width, int *height)
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

void			check_neighbours(t_map_data *map_data, int mx, int my)
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
	if (ft_strchr(MP_INNER_OBJECTS, (map_data->map)[my][mx]) && \
		(mx == map_data->width - 1 || my == map_data->height - 1))
		exit_failure("Map breach detected at position [%s][%s]\n", \
		ft_itoa(mx, 10), ft_itoa(my, 10));
}
