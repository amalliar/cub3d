/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_handler.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 10:44:40 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/06 11:17:12 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYPRESS_HANDLER_H
# define KEYPRESS_HANDLER_H

# include "cub3d.h"
# include "mlx.h"
# include "keycodes.h"
# include "graphics.h"
# include "ft_stdlib.h"
# include "ft_string.h"

int			keypress_handler(int keycode, t_scene *scene);
void		process_interact_request(t_scene *scene);
t_door		*get_door(t_scene *scene, int door_x, int door_y);

#endif
