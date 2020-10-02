/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:11:55 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 19:16:34 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_params.h"

void	check_format(char **rgb_values, char **words)
{
	int		wc;

	wc = word_count(rgb_values);
	if (wc != 3)
		exit_failure("Invalid R,G,B format: %s\n", words[1]);
	if (!ft_strisnumeric(rgb_values[0]) || !ft_strisnumeric(rgb_values[1]) || \
		!ft_strisnumeric(rgb_values[2]))
		exit_failure("Invalid R,G,B format: %s\n", words[1]);
	if (strisbignum(rgb_values[0]) || strisbignum(rgb_values[1]) || \
		strisbignum(rgb_values[1]))
		exit_failure("Invalid R,G,B value: %s\n", words[1]);
}

void	set_texture(t_scene *scene, char **words)
{
	int		wc;
	int		width;
	int		height;
	void	*img;

	wc = word_count(words);
	if (wc != 2)
		exit_failure("Incorrect number of parameters for texture %s: "
		"expected 1 but got %s\n", words[0], ft_itoa(wc - 1, 10));
	if (!(img = mlx_xpm_file_to_image((scene->mlx_data).mlx, words[1], \
		&width, &height)))
		exit_failure("Failed creating mlx image instance from file %s: %s\n", \
		words[1], strerror(errno));
	if (!ft_strcmp("NO", words[0]))
		set_mlx_image(&(scene->textures).walls.north, img, width, height);
	else if (!ft_strcmp("SO", words[0]))
		set_mlx_image(&(scene->textures).walls.south, img, width, height);
	else if (!ft_strcmp("WE", words[0]))
		set_mlx_image(&(scene->textures).walls.west, img, width, height);
	else if (!ft_strcmp("EA", words[0]))
		set_mlx_image(&(scene->textures).walls.east, img, width, height);
}

void	free_split_tab(char **words)
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
