/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_enemie_states.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 00:23:36 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/29 15:08:42 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_ENEMIE_STATES_H
# define PROCESS_ENEMIE_STATES_H
# define EN_MAX_VIEWING_DIST	20
# define EN_INTERACT_DIST		6

# include "ft_stdlib.h"
# include "graphics.h"
# include "process_physics.h"
# include "textures.h"

bool	player_out_of_scope(t_scene *scene, t_sprite *en);
void	adjust_view_dir(t_scene *scene, t_sprite *en);
void	alert_neighbours(t_scene *scene, t_sprite *en);
void	drop_ammo_and_score_points(t_scene *scene, t_sprite *en);
void	check_player_presence(t_scene *scene, t_sprite *en);
void	start_player_tracking(t_scene *scene, t_sprite *en);
void	enemie_attack(t_scene *scene, t_sprite *en);

#endif
