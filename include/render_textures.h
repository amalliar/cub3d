/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:54:34 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 19:01:30 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_TEXTURES_H
# define RENDER_TEXTURES_H

void	calculate_stripe_limits(t_player_data *pd, int height);
void	calculate_tex_x(t_scene *scene, t_mlx_image *texture);
void	dda_init1(t_player_data *pd, int x, int width);
void	dda_init2(t_player_data *pd);
void	dda_run(t_player_data *pd, t_map_data *md);
void	fill_stripe(t_scene *scene, t_mlx_image *texture, int x);
void	pick_texture(t_scene *scene, t_mlx_image **texture);

#endif
