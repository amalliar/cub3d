/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_physics.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 22:18:56 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/27 08:39:05 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_PHYSICS_H
# define PROCESS_PHYSICS_H

# include "process_key_states.h"
# include "render_scene.h"
# include "snd.h"
# include "ft_string.h"

void	player_attack(t_scene *scene);
void	process_secret_states(t_scene *scene);
void	process_weapon_state(t_scene *scene);

#endif
