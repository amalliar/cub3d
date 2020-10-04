/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 21:47:42 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/04 17:32:35 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_map.h"

void	get_map_size(t_list *lst, int *width, int *height)
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

void	gen_map_line(char *dest, char *src, int max_len)
{
	int		len;

	len = ft_strlen(src);
	if (max_len < len)
		len = max_len;
	ft_memcpy(dest, src, len);
	while (len < max_len)
	{
		dest[len] = ' ';
		++len;
	}
	dest[max_len] = '\0';
}

void	process_map_object(t_scene *scene, int x, int y, char obj)
{
	if (ft_strchr(MP_INNER_OBJECTS, obj))
		check_neighbours(&scene->map_data, x, y);
	if (ft_strchr("^_<>", obj))
	{
		load_player_data(&scene->player_data, x, y, obj);
		((scene->map_data).map)[y][x] = '0';
	}
	else if (ft_strchr(MP_OBJECTS, obj))
		load_object_data(scene, x, y, obj);
	else if (ft_strchr(MP_ENEMIES, obj))
		load_enemie_data(scene, x, y, obj);
	else if (ft_strchr(MP_DOORS, obj))
		load_door_data(scene, x, y, obj);
	else if (ft_strchr(MP_SECRETS, obj))
		load_secret_data(scene, x, y, obj);
}

int		get_cur_line_length(char *line)
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

void	check_neighbours(t_map_data *md, int mx, int my)
{
	if (mx > 0 && (md->map)[my][mx - 1] == ' ')
		exit_failure("Map breach detected at position [%s][%s]\n", \
		ft_itoa(mx + 1, 10), ft_itoa(my + 1, 10));
	if (mx < md->width - 1 && (md->map)[my][mx + 1] == ' ')
		exit_failure("Map breach detected at position [%s][%s]\n", \
		ft_itoa(mx + 1, 10), ft_itoa(my + 1, 10));
	if (my > 0 && (md->map)[my - 1][mx] == ' ')
		exit_failure("Map breach detected at position [%s][%s]\n", \
		ft_itoa(mx + 1, 10), ft_itoa(my + 1, 10));
	if (my < md->height - 1 && (md->map)[my + 1][mx] == ' ')
		exit_failure("Map breach detected at position [%s][%s]\n", \
		ft_itoa(mx + 1, 10), ft_itoa(my + 1, 10));
	if (ft_strchr(MP_INNER_OBJECTS, (md->map)[my][mx]) && \
		(mx == md->width - 1 || my == md->height - 1))
		exit_failure("Map breach detected at position [%s][%s]\n", \
		ft_itoa(mx + 1, 10), ft_itoa(my + 1, 10));
}
