/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:17:56 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/25 01:08:42 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define CLR_WHITE		0xFFFFFF
# define CLR_SILVER		0xC0C0C0
# define CLR_GRAY		0x808080
# define CLR_BLACK		0x000000
# define CLR_RED		0xFF0000
# define CLR_MAROON		0x800000
# define CLR_YELLOW		0xFFFF00
# define CLR_OLIVE		0x808000
# define CLR_LIME		0x00FF00
# define CLR_GREEN		0x008000
# define CLR_AQUA		0x00FFFF
# define CLR_TEAL		0x008080
# define CLR_BLUE		0x0000FF
# define CLR_NAVY		0x000080
# define CLR_FUCHSIA	0xFF00FF
# define CLR_PURPLE		0x800080
# define CLR_NAN		0x980088
# define CLR_BLOOD		0x880000

int		clr_create(int a, int r, int g, int b);
int		clr_get_alpha(int color);
int		clr_get_red(int color);
int		clr_get_green(int color);
int		clr_get_blue(int color);
int		clr_mix(int color1, int color2, double amount);

#endif
