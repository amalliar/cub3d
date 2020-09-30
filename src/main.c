/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:38:20 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/30 12:21:01 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		init_scene(t_scene **pscene)
{
	t_scene		*scene;

	if (!(*pscene = malloc(sizeof(t_scene))))
		exit_failure("%s\n", strerror(errno));
	scene = *pscene;
	init_mlx_data(&scene->mlx_data);
	init_key_and_button_states(&scene->key_states, &scene->button_states);
	init_player_data(&scene->player_data);
	(scene->sprite_data).num_sprites = 0;
	scene->num_doors = 0;
	scene->num_secrets = 0;
	scene->render_started = 0;
	scene->mouse_grabbing = DISABLED;
	scene->game_state = GS_NORMAL;
	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
	srand(time(NULL));
}

static void		get_render_mode(int argc, char **argv, int *render_mode)
{
	if (argc < 2)
		exit_failure("Program requires at least one argument (scene.cub)\n");
	if (!ft_strmatch("*.cub", argv[1]))
		exit_failure("Unknown file type: %s\n", argv[1]);
	if (argc > 3)
		exit_failure("Too many arguments\n");
	if (argc == 3)
	{
		if (!ft_strcmp("--save", argv[2]))
		{
			*render_mode = SCREENSHOT;
			return ;
		}
		else
			exit_failure("Unknown argument: %s\n", argv[2]);
	}
	*render_mode = LOOP;
}

int				main(int argc, char **argv)
{
	t_scene		*scene;
	int			render_mode;

	get_render_mode(argc, argv, &render_mode);
	init_scene(&scene);
	load_scene(scene, argv[1]);
	if (render_mode == SCREENSHOT)
	{
		take_screenshot(scene);
		exit(EXIT_SUCCESS);
	}
	render_scene(scene);
	exit(EXIT_SUCCESS);
}
