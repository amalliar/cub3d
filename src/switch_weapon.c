/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:22:06 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 16:22:21 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_press_handler.h"

void		switch_weapon(t_player_data *pd, int id)
{
	if ((pd->weapons)[id].unlocked == false)
		return ;
	pd->active_weapon->frame = 0;
	pd->active_weapon->state = IDLE;
	pd->active_weapon = pd->weapons + id;
}
