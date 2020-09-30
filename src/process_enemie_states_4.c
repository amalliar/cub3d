/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_enemie_states_4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 05:00:07 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/30 11:00:11 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_enemie_states.h"

static int		calculate_attack_damage(t_scene *scene, t_sprite *en)
{
	t_key_states	*ks;
	int				speed;
	int				look;
	int				rand1;
	int				rand2;

	ks = &scene->key_states;
	if ((ks->xk_w == KEY_DOWN || ks->xk_s == KEY_DOWN || \
		ks->xk_a == KEY_DOWN || ks->xk_d == KEY_DOWN) && \
		(scene->player_data).pos_z >= 0)
		speed = 160;
	else
		speed = 256;
	look = (en->is_visible) ? 16 : 8;
	rand1 = rand() % 256;
	rand2 = rand() % 256;
	if (rand1 >= (speed - (en->dist * look)))
		return (0);
	if (en->dist < 2)
		return (rand2 / 4);
	else if (en->dist >= 2 && en->dist < 4)
		return (rand2 / 8);
	else
		return (rand2 / 16);
}

void			enemie_attack(t_scene *scene, t_sprite *en)
{
	t_player_data	*pd;
	int				damage;

	pd = &scene->player_data;
	if (player_out_of_scope(scene, en))
		return ;
	damage = calculate_attack_damage(scene, en);
	if (damage == 0)
		return ;
	pd->health -= damage;
	if (pd->health <= 0)
	{
		pd->health = 0;
		playMusicFromMemory((scene->music)[0], 0);
		playSoundFromMemory((scene->sounds)[SND_PLAYER_DEATH], G_SOUNDS_VOLUME);
		scene->game_state = GS_DEATH;
		(pd->effects).r_player_dead = clock();
		return ;
	}
	else if (damage < 20)
		playSoundFromMemory((scene->sounds)[SND_PLAYER_PAIN], G_SOUNDS_VOLUME);
	else
		playSoundFromMemory((scene->sounds)[SND_PLAYER_PAIN_CRITICAL], \
			G_SOUNDS_VOLUME);
	(pd->effects).r_player_hit = clock();
}
