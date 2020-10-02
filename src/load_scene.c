/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 22:31:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/02 18:32:26 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_scene.h"

void	load_scene(t_scene *scene, char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		exit_failure("Can't open %s: %s\n", path, strerror(errno));
	load_params(scene, fd);
	load_map(scene, fd);
	close(fd);
}
