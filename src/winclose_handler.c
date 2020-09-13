/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winclose_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:45:08 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/13 19:50:26 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		winclose_handler(t_scene *scene)
{
	(void)scene;
	endAudio();
	SDL_Quit();
	exit(EXIT_SUCCESS);
	return (0);
}
