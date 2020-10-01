/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:06:34 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/01 12:33:13 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_scene.h"
#include "colors.h"
#include "ft_stdlib.h"
#include "ft_string.h"

void			free_split_tab(char **words)
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

int				word_count(char **words)
{
	int		i;

	i = 0;
	while (words[i] != NULL)
		++i;
	return (i);
}

static void		check_format(char **rgb_values, char **words)
{
	int		wc;

	wc = word_count(rgb_values);
	if (wc != 3)
		exit_failure("Invalid R,G,B format: %s\n", words[1]);
	if (((ft_strchr("-+", rgb_values[0][0])) ?
		!ft_strisnumeric(rgb_values[0] + 1) : !ft_strisnumeric(rgb_values[0])) \
		|| ((ft_strchr("-+", rgb_values[1][0])) ?
		!ft_strisnumeric(rgb_values[1] + 1) : !ft_strisnumeric(rgb_values[1])) \
		|| ((ft_strchr("-+", rgb_values[2][0])) ?
		!ft_strisnumeric(rgb_values[2] + 1) : !ft_strisnumeric(rgb_values[2])))
		exit_failure("Invalid R,G,B format: %s\n", words[1]);
}

void			set_color(t_colors *colors, char **words)
{
	int		wc;
	int		r;
	int		g;
	int		b;
	char	**rgb_values;

	wc = word_count(words);
	if (wc != 2)
		exit_failure("Incorrect number of parameters for color: "
		"expected 1 but got %s\n", ft_itoa(wc - 1, 10));
	if (!(rgb_values = ft_split(words[1], ',')))
		exit_failure("%s\n", strerror(errno));
	check_format(rgb_values, words);
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	free_split_tab(rgb_values);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_failure("Invalid R,G,B value: %s\n", words[1]);
	if (!ft_strcmp("F", words[0]) && colors->floor == -1)
		colors->floor = clr_create(0, r, g, b);
	else if (!ft_strcmp("C", words[0]) && colors->ceilling == -1)
		colors->ceilling = clr_create(0, r, g, b);
	else
		exit_failure("Double initialisation of floor/ceilling color\n");
}
