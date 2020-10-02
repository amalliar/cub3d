/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:02:28 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 19:25:13 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_PARAMS_H
# define LOAD_PARAMS_H
# define MANDATORY_PARAMS_COUNT		8
# define PARAMS_LOADED				200

# include "colors.h"
# include "cub3d.h"
# include "ft_stdio.h"
# include "ft_stdlib.h"
# include "ft_string.h"

int		parse_params(t_scene *scene, char *line);
int		strisbignum(char *str);
int		word_count(char **words);
void	check_format(char **rgb_values, char **words);
void	check_illegal_commas(char *str);
void	free_split_tab(char **words);
void	set_color(t_colors *colors, char **words);
void	set_mlx_image(t_mlx_image *mlx_image, void *img, int width, int height);
void	set_resolution(t_mlx_data *mlx_data, char **words);
void	set_sprite(t_scene *scene, char **words);
void	set_texture(t_scene *scene, char **words);

#endif
