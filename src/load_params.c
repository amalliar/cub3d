/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 17:58:00 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/06 15:55:08 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_scene.h"
#include "load_params.h"

#define INT_MAX_LEN			10
#define INT_MAX_STR			"2147483647"

void			load_params(t_scene *scene, int fd)
{
	int		ret;
	char	*line;

	if ((ret = ft_get_next_line(fd, &line)) < 0)
		exit_failure("Failed reading from a file descriptor: %s\n", \
		strerror(errno));
	if (ft_strlen(line) == 0)
		exit_failure("Scene file can not start with empty line(s)\n");
	parse_params(scene, line);
	free(line);
	while ((ret = ft_get_next_line(fd, &line)) > 0)
	{
		ret = parse_params(scene, line);
		free(line);
		if (ret == PARAMS_LOADED)
			break ;
	}
	if (ret == 0)
		exit_failure("%s\n", \
		"Scene file is missing mandatory configuration parameters");
}

static void		check_illegal_spaces(char *str)
{
	if (*str == ' ' || *(str + ft_strlen(str) - 1) == ' ')
		exit_failure("Spaces can only be used to separate elements\n");
}

int				parse_params(t_scene *scene, char *line)
{
	static int		unset_params = MANDATORY_PARAMS_COUNT;
	char			**words;

	if (ft_strlen(line) == 0)
		return (0);
	check_illegal_spaces(line);
	if (!(words = ft_split(line, ' ')))
		exit_failure("%s\n", strerror(errno));
	if (ft_strstr("R", words[0]))
		set_resolution(&scene->mlx_data, words);
	else if (ft_strstr("S", words[0]))
		set_sprite(scene, words);
	else if (ft_strstr("F C", words[0]))
		set_color(&scene->colors, words);
	else if (ft_strstr("NO SO WE EA", words[0]))
		set_texture(scene, words);
	else
		exit_failure("Unknown configuration parameter: %s\n", words[0]);
	free_split_tab(words);
	--unset_params;
	return ((unset_params == 0) ? PARAMS_LOADED : 0);
}

void			set_resolution(t_mlx_data *mlx_data, char **words)
{
	int		wc;
	int		width;
	int		height;

	if (mlx_data->width != 0)
		exit_failure("Double initialisation of resolution\n");
	wc = word_count(words);
	if (wc != 3)
		exit_failure("Incorrect number of parameters for resolution: "
		"expected 2 but got %s\n", ft_itoa(wc - 1, 10));
	if (!ft_strisnumeric(words[1]) || !ft_strisnumeric(words[2]))
		exit_failure("Invalid resolution format: %s %s\n", words[1], words[2]);
	width = (strisbignum(words[1])) ? INT_MAX : ft_atoi(words[1]);
	height = (strisbignum(words[2])) ? INT_MAX : ft_atoi(words[2]);
	if (width == 0 || height == 0)
		exit_failure("Invalid resolution value: %s\n", \
		(width == 0) ? words[1] : words[2]);
	mlx_get_screen_size(mlx_data->mlx, &mlx_data->width, &mlx_data->height);
	if (width < mlx_data->width)
		mlx_data->width = width;
	if (height < mlx_data->height)
		mlx_data->height = height;
}

int				strisbignum(char *str)
{
	size_t		len;

	while (*str == '0')
		++str;
	len = ft_strlen(str);
	if (len != INT_MAX_LEN)
		return (len > INT_MAX_LEN);
	return ((ft_strcmp(str, INT_MAX_STR) > 0) ? 1 : 0);
}
