/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_integer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 06:42:55 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/20 21:34:22 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"
#include "ft_stdio.h"
#include "ft_stdlib.h"

static void		print_sign(t_printf_info *info, intmax_t num)
{
	if (num >= 0)
	{
		if (info->flags & FLG_PLUS)
			ft_putchar('+');
		else if (info->flags & FLG_SPACE)
			ft_putchar(' ');
	}
	else
		ft_putchar('-');
}

static int		type_regular(t_printf_info *info, intmax_t num)
{
	char	*str;
	char	pchar;
	int		padding;
	int		nlen;
	int		nwidth;

	str = ft_itoa(num, 10);
	nlen = ft_strlen(str) - (num < 0);
	if (info->precision == 0 && num == 0)
		nlen = 0;
	padding = (info->precision > nlen) ? info->precision - nlen : 0;
	nwidth = (num < 0 || info->flags & (FLG_PLUS | FLG_SPACE)) + nlen + padding;
	pchar = ((info->flags & FLG_ZERO) && (info->precision < 0)) ? '0' : ' ';
	if (pchar == '0')
		print_sign(info, num);
	if ((info->width > nwidth) && !(info->flags & FLG_MINUS))
		ft_putnchar(pchar, info->width - nwidth);
	if (pchar == ' ')
		print_sign(info, num);
	ft_putnchar('0', padding);
	ft_putnstr((*str == '-') ? str + 1 : str, nlen);
	free(str);
	if ((info->width > nwidth) && (info->flags & FLG_MINUS))
		ft_putnchar(pchar, info->width - nwidth);
	return ((info->width > nwidth) ? info->width : nwidth);
}

int				form_integer(t_printf_info *info, va_list *ap)
{
	if (!ft_strcmp(info->length, ""))
		return (type_regular(info, va_arg(*ap, int)));
	else if (!ft_strcmp(info->length, "hh"))
		return (type_regular(info, (signed char)va_arg(*ap, int)));
	else if (!ft_strcmp(info->length, "h"))
		return (type_regular(info, (short int)va_arg(*ap, int)));
	else if (!ft_strcmp(info->length, "l"))
		return (type_regular(info, va_arg(*ap, long int)));
	else if (!ft_strcmp(info->length, "ll"))
		return (type_regular(info, va_arg(*ap, long long int)));
	else if (!ft_strcmp(info->length, "j"))
		return (type_regular(info, va_arg(*ap, intmax_t)));
	else if (!ft_strcmp(info->length, "z"))
		return (type_regular(info, va_arg(*ap, size_t)));
	else if (!ft_strcmp(info->length, "t"))
		return (type_regular(info, va_arg(*ap, ptrdiff_t)));
	return (0);
}
