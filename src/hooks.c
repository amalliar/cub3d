/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:15:08 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/31 20:37:49 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "graphics.h"
#include "ft_stdio.h"

int				print_keycode(int keycode, t_vars *vars)
{
	(void)vars;
	ft_printf("keycode: %d\n", keycode);
	return (keycode);
}

int				print_mouse_pos(t_vars *vars)
{
	static int		old_x = -1;
	static int		old_y = -1;
	int				cur_x;
	int				cur_y;

	mlx_mouse_get_pos(vars->win, &cur_x, &cur_y);
	if (cur_x != old_x && cur_y != old_y)
		ft_printf("mouse position: x: %d, y: %d\n", cur_x, cur_y);
	old_x = cur_x;
	old_y = cur_y;
	return (0);
}

int				main(void)
{
	t_vars		vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "cub3D");
	mlx_key_hook(vars.win, print_keycode, &vars);
	mlx_loop_hook(vars.mlx, print_mouse_pos, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
