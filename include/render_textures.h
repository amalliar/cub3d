/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 16:54:17 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/16 17:05:10 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_TEXTURES_H
# define RENDER_TEXTURES_H
# include "cub3d.h"
# include "graphics.h"

void	render_textures(t_scene *scene);
void	pick_texture(t_scene *scene, t_mlx_image **texture);
void	calc_tex_x(t_scene *scene, t_mlx_image *texture);
void	fill_stripe(t_scene *scene, t_mlx_image *texture, int x);

#endif
