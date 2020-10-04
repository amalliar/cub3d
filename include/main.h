/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 04:36:57 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/03 20:56:39 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "cub3d.h"
# include "ft_stdlib.h"
# include "ft_string.h"
# include "mlx.h"

void	init_mlx_data(t_mlx_data *mlx_data);
void	init_key_and_button_states(t_key_states *ks, \
			t_button_states *bs);
void	init_player_data(t_player_data *pd);
void	load_scene(t_scene *scene, char *path);
void	render_scene(t_scene *scene);

#endif
