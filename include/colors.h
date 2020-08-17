/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:17:56 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/17 15:16:53 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define WHITE		0xFFFFFF
# define SILVER		0xC0C0C0
# define GRAY		0x808080
# define BLACK		0x000000
# define RED		0xFF0000
# define MAROON		0x800000
# define YELLOW		0xFFFF00
# define OLIVE		0x808000
# define LIME		0x00FF00
# define GREEN		0x008000
# define AQUA		0x00FFFF
# define TEAL		0x008080
# define BLUE		0x0000FF
# define NAVY		0x000080
# define FUCHSIA	0xFF00FF
# define PURPLE		0x800080

int		clr_create(int a, int r, int g, int b);
int		clr_get_alpha(int color);
int		clr_get_red(int color);
int		clr_get_green(int color);
int		clr_get_blue(int color);

#endif
