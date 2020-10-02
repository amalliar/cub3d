/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keystates.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:47:43 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 18:49:49 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_KEYSTATES_H
# define PROCESS_KEYSTATES_H

# include "cub3d.h"
# include "keycodes.h"

void	move_backward(t_map_data *md, t_player_data *pd);
void	move_forward(t_map_data *md, t_player_data *pd);
void	move_left(t_map_data *md, t_player_data *pd);
void	move_right(t_map_data *md, t_player_data *pd);
void	turn_left(t_player_data *pd);
void	turn_right(t_player_data *pd);

#endif
