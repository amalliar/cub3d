/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 07:15:42 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/20 21:38:17 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"
#include "ft_stdlib.h"
#include "ft_stdio.h"

/*
** if 1 / num > 0, num == +0
** if 1 / num < 0, num == -0
*/

static void		print_sign(t_printf_info *info, long double num)
{
	if (num > 0 || (num == 0 && 1 / num > 0))
	{
		if (info->flags & FLG_PLUS)
			ft_putchar('+');
		else if (info->flags & FLG_SPACE)
			ft_putchar(' ');
	}
	else
		ft_putchar('-');
}

static int		type_regular(t_printf_info *info, long double num)
{
	char	*str;
	char	pchar;
	int		nlen;
	int		nwidth;

	str = (info->form == 'F') ? ft_strtoupper(ft_ftoa(num, info->precision)) : \
		ft_ftoa(num, info->precision);
	nlen = ft_strlen(str) - (num < 0);
	nwidth = (num < 0 || 1 / num < 0 || info->flags & (FLG_PLUS | FLG_SPACE)) \
		+ nlen + ((info->flags & FLG_HASH) && ft_strchr(str, '.') == NULL);
	pchar = (info->flags & FLG_ZERO) ? '0' : ' ';
	if (pchar == '0')
		print_sign(info, num);
	if ((info->width > nwidth) && !(info->flags & FLG_MINUS))
		ft_putnchar(pchar, info->width - nwidth);
	if (pchar == ' ')
		print_sign(info, num);
	ft_putnstr((*str == '-') ? str + 1 : str, nlen);
	if ((info->flags & FLG_HASH) && !ft_strchr(str, '.') && \
		!ft_strchr(str, 'n') && !ft_strchr(str, 'N'))
		ft_putchar('.');
	free(str);
	if ((info->width > nwidth) && (info->flags & FLG_MINUS))
		ft_putnchar(pchar, info->width - nwidth);
	return ((info->width > nwidth) ? info->width : nwidth);
}

int				form_float(t_printf_info *info, va_list *ap)
{
	if (info->precision < 0)
		info->precision = 6;
	if (info->form == 'f' || info->form == 'F')
	{
		if (!ft_strcmp(info->length, ""))
			return (type_regular(info, va_arg(*ap, double)));
		else if (!ft_strcmp(info->length, "L"))
			return (type_regular(info, va_arg(*ap, long double)));
	}
	return (0);
}
