/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:38:20 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/05 05:48:04 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "ft_string.h"
#include "ft_stdlib.h"

static void		init_keystates(t_keystates *ks)
{
	ks->kvk_ansi_w = KEY_UP;
	ks->kvk_ansi_a = KEY_UP;
	ks->kvk_ansi_s = KEY_UP;
	ks->kvk_ansi_d = KEY_UP;
	ks->kvk_leftarrow = KEY_UP;
	ks->kvk_rightarrow = KEY_UP;
	ks->kvk_uparrow = KEY_UP;
	ks->kvk_downarrow = KEY_UP;
}

static void		init_scene(t_scene *scene)
{
	t_mlx_data		*mlx_data;

	mlx_data = &scene->mlx_data;
	if ((mlx_data->mlx = mlx_init()) == NULL)
		exit_failure("Failed creating mlx instance\n");
	mlx_data->win = NULL;
	mlx_get_screen_size(mlx_data->mlx, &mlx_data->width, &mlx_data->height);
	if (mlx_data->width < MLX_WINDOW_WIDTH || \
		mlx_data->height < MLX_WINDOW_HEIGHT)
		exit_failure("Resolution %sx%s is unsupported by this screen.\n", \
			ft_itoa(MLX_WINDOW_WIDTH, 10), ft_itoa(MLX_WINDOW_HEIGHT, 10));
	mlx_data->width = MLX_WINDOW_WIDTH;
	mlx_data->height = MLX_WINDOW_HEIGHT;
	(*scene).sprite_data.num_sprites = 0;
	(*scene).player_data.pos_x = -1;
	(*scene).player_data.v0 = 0;
	(*scene).player_data.level = 0;
	init_keystates(&scene->keystates);
	(*scene).mouse_grabbing = DISABLED;
	(*scene).render_started = 0;
}

static void		get_render_mode(int argc, char **argv, int *render_mode)
{
	if (argc < 2)
		exit_failure("Program requires at least one argument (scene.cub)\n");
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
