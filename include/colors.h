/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:17:56 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/29 22:11:23 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H
# define WHITE		0x00FFFFFF
# define SILVER		0x00C0C0C0
# define GRAY		0x00808080
# define BLACK		0x00000000
# define RED		0x00FF0000
# define MAROON		0x00800000
# define YELLOW		0x00FFFF00
# define OLIVE		0x00808000
# define LIME		0x0000FF00
# define GREEN		0x00008000
# define AQUA		0x0000FFFF
# define TEAL		0x00008080
# define BLUE		0x000000FF
# define NAVY		0x00000080
# define FUCHSIA	0x00FF00FF
# define PURPLE		0x00800080

int		create_color(int a, int r, int g, int b);
int		get_alpha(int color);
int		get_red(int color);
int		get_green(int color);
int		get_blue(int color);
int		add_shade(double distance, int color);
int		get_opposite(int color);

#endif
