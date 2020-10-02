/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:04:56 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 19:24:21 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_params.h"

int				word_count(char **words)
{
	int		i;

	i = 0;
	while (words[i] != NULL)
		++i;
	return (i);
}

void			set_sprite(t_scene *scene, char **words)
{
	int		wc;
	int		width;
	int		height;
	void	*img;

	wc = word_count(words);
	if (wc != 2)
		exit_failure("Incorrect number of parameters for sprite: "
		"expected 1 but got %s\n", ft_itoa(wc - 1, 10));
	if (!(img = mlx_xpm_file_to_image((scene->mlx_data).mlx, words[1], \
		&width, &height)))
		exit_failure("Failed creating mlx image instance from file %s: %s\n", \
		words[1], strerror(errno));
	set_mlx_image(&(scene->textures).sprite, img, width, height);
}

void			set_mlx_image(t_mlx_image *mlx_image, void *img, \
					int width, int height)
{
	if (mlx_image->img != NULL)
		exit_failure("Double initialisation of texture/sprite\n");
	mlx_image->img = img;
	mlx_image->width = width;
	mlx_image->height = height;
	mlx_image->addr = mlx_get_data_addr(mlx_image->img, \
	&mlx_image->bits_per_pixel, &mlx_image->line_length, &mlx_image->endian);
}

void			set_color(t_colors *colors, char **words)
{
	int		wc;
	int		r;
	int		g;
	int		b;
	char	**rgb_values;

	if ((wc = word_count(words)) != 2)
		exit_failure("Incorrect number of parameters for color: "
		"expected 1 but got %s\n", ft_itoa(wc - 1, 10));
	check_illegal_commas(words[1]);
	if (!(rgb_values = ft_split(words[1], ',')))
		exit_failure("%s\n", strerror(errno));
	check_format(rgb_values, words);
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	free_split_tab(rgb_values);
	if (r > 255 || g > 255 || b > 255)
		exit_failure("Invalid R,G,B value: %s\n", words[1]);
	if (!ft_strcmp("F", words[0]) && colors->floor == -1)
		colors->floor = clr_create(0, r, g, b);
	else if (!ft_strcmp("C", words[0]) && colors->ceilling == -1)
		colors->ceilling = clr_create(0, r, g, b);
	else
		exit_failure("Double initialisation of floor/ceilling color\n");
}

void			check_illegal_commas(char *str)
{
	int		num_commas;
	char	*ptr;

	if (*str == ',' || *(str + ft_strlen(str) - 1) == ',')
		exit_failure("Invalid R,G,B format: %s\n", str);
	num_commas = 0;
	ptr = str;
	while (*ptr)
		if (*ptr++ == ',')
			++num_commas;
	if (num_commas != 2)
		exit_failure("Invalid R,G,B format: %s\n", str);
}
