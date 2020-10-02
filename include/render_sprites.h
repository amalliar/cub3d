/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:02:54 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 19:14:33 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_SPRITES_H
# define RENDER_SPRITES_H
# define U_DIV				1
# define V_DIV 				1
# define V_MOVE 			0.0
# define BACKGROUND			0x980088

# include "ft_stdlib.h"

void	init_sprite_data(t_mlx_data *md, t_player_data *pd, t_sprite_data *sd);
void	draw_sprite(t_scene *scene, t_mlx_data *md, t_player_data *pd, \
			t_sprite_data *sd);

#endif
