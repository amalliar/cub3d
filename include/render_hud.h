/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 18:39:52 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/29 10:51:13 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_HUD_H
# define RENDER_HUD_H

# include "colors.h"
# include "graphics.h"

void		draw_crosshair(t_scene *scene);
void		draw_fps_box(t_scene *scene);

#endif
