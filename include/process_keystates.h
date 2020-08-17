/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keystates.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:47:43 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/17 21:43:28 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_KEYSTATES_H
# define PROCESS_KEYSTATES_H
# include "cub3d.h"

void	set_player_speed(t_player_data *pd, t_mlx_data *mlx_data);
void	turn_left(t_player_data *pd);
void	turn_right(t_player_data *pd);

#endif
