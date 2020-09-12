/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 11:11:44 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 13:21:28 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_WALLS_H
# define RENDER_WALLS_H

# include "graphics.h"
# include "key_press_handler.h"
# include "render_scene.h"

void	calc_texture_x(t_scene *scene, t_mlx_image *texture);
void	check_door_hit(t_scene *scene, t_player_data *pd, t_map_data *md);
void	extend_ray(t_scene *scene);
void	fill_stripe(t_scene *scene, t_mlx_image *texture, int x);
void	select_texture(t_scene *scene, t_mlx_image **texture);

#endif
