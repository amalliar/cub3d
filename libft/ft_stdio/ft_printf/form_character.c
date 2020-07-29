/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_character.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 07:18:06 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/15 22:41:06 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"
#include "ft_stdio.h"

/*
** Note: this function is supposed to be able to print wide characters,
** but I don't know how to do this without using wctomb().
*/

static int	type_wide(t_printf_info *info, wint_t wc)
{
	char	pchar;

	if (info->width > 1)
	{
		pchar = (info->flags & FLG_ZERO) ? '0' : ' ';
		if (!(info->flags & FLG_MINUS))
			ft_putnchar(pchar, info->width - 1);
		ft_putchar(wc);
		if (info->flags & FLG_MINUS)
			ft_putnchar(pchar, info->width - 1);
		return (info->width);
	}
	ft_putchar(wc);
	return (1);
}

static int	type_regular(t_printf_info *info, int c)
{
	char	pchar;

	if (info->width > 1)
	{
		pchar = (info->flags & FLG_ZERO) ? '0' : ' ';
		if (!(info->flags & FLG_MINUS))
			ft_putnchar(pchar, info->width - 1);
		ft_putchar(c);
		if (info->flags & FLG_MINUS)
			ft_putnchar(pchar, info->width - 1);
		return (info->width);
	}
	ft_putchar(c);
	return (1);
}

int			form_character(t_printf_info *info, va_list *ap)
{
	if (!ft_strcmp(info->length, "l"))
		return (type_wide(info, va_arg(*ap, wint_t)));
	else
		return (type_regular(info, va_arg(*ap, int)));
}
