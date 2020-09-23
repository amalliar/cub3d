/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_enemie_states.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 00:23:36 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/24 02:17:12 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_ENEMIE_STATES_H
# define PROCESS_ENEMIE_STATES_H
# define EN_MAX_VIEWING_DISTANCE	20

# include "ft_stdlib.h"
# include "graphics.h"
# include "process_physics.h"
# include "textures.h"

void	drop_ammo(t_scene *scene, t_sprite *en);
void	check_player_presence(t_scene *scene, t_sprite *en);
void	start_player_tracking(t_scene *scene, t_sprite *en);

#endif
