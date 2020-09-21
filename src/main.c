/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:38:20 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/21 22:52:21 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "mlx.h"

static void		init_mlx_data(t_mlx_data *mlx_data)
{
	if (!(mlx_data->mlx = mlx_init()))
		exit_failure("Failed creating mlx instance\n");
	mlx_data->win = NULL;
	mlx_get_screen_size(mlx_data->mlx, &mlx_data->width, &mlx_data->height);
	if (mlx_data->width < G_MLX_WINDOW_WIDTH || \
		mlx_data->height < G_MLX_WINDOW_HEIGHT)
		exit_failure("Resolution %sx%s is unsupported by this screen.\n", \
			ft_itoa(G_MLX_WINDOW_WIDTH, 10), ft_itoa(G_MLX_WINDOW_HEIGHT, 10));
	mlx_data->width = G_MLX_WINDOW_WIDTH;
	mlx_data->height = G_MLX_WINDOW_HEIGHT;
}

static void		init_key_and_button_states(t_key_states *ks, \
					t_button_states *bs)
{
	ks->kvk_ansi_w = KEY_UP;
	ks->kvk_ansi_a = KEY_UP;
	ks->kvk_ansi_s = KEY_UP;
	ks->kvk_ansi_d = KEY_UP;
	ks->kvk_leftarrow = KEY_UP;
	ks->kvk_rightarrow = KEY_UP;
	ks->kvk_uparrow = KEY_UP;
	ks->kvk_downarrow = KEY_UP;
	bs->mb_left = KEY_UP;
	bs->mb_right = KEY_UP;
	bs->mb_middle = KEY_UP;
	bs->mb_wheel_up = KEY_UP;
	bs->mb_wheel_down = KEY_UP;
}

static void		init_scene(t_scene *scene)
{
	init_mlx_data(&scene->mlx_data);
	init_key_and_button_states(&scene->key_states, &scene->button_states);
	(*scene).sprite_data.num_sprites = 0;
	(*scene).num_doors = 0;
	(*scene).num_secrets = 0;
	(*scene).player_data.pos_x = -1;
	(*scene).player_data.v0 = 0;
	(*scene).player_data.level = 0;
	(*scene).player_data.facecount = 0;
	(*scene).player_data.r_facetimer = 0;
	(*scene).player_data.faceframe = 1;
	(*scene).player_data.effects.r_bj_evil_grin = 0;
	(*scene).render_started = 0;
	(*scene).mouse_grabbing = DISABLED;
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
	t_scene		scene;
	int			render_mode;

	get_render_mode(argc, argv, &render_mode);
	init_scene(&scene);
	load_scene(&scene, argv[1]);
	if (render_mode == SCREENSHOT)
	{
		take_screenshot(&scene);
		exit(EXIT_SUCCESS);
	}
	render_scene(&scene);
	exit(EXIT_SUCCESS);
}
