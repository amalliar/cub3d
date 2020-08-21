/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:50:36 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/21 17:27:00 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_SCENE_H
# define RENDER_SCENE_H
# include <time.h>
# include "cub3d.h"
# include "graphics.h"

void	render_scene(t_scene *scene, int mode);
void	process_keystates(t_scene *scene);
void	render_textures(t_scene *scene);
void	select_texture(t_scene *scene, t_mlx_image **texture);
void	calc_texture_x(t_scene *scene, t_mlx_image *texture);
void	fill_stripe(t_scene *scene, t_mlx_image *texture, int x);
void	render_sprites(t_scene *scene);

#endif
