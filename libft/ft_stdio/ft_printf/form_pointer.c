/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_pointer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 07:19:21 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/14 22:30:43 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"
#include "ft_stdlib.h"
#include "ft_stdio.h"

int		form_pointer(t_printf_info *info, va_list *ap)
{
	uintmax_t	addr;
	char		*str;
	int			awidth;

	addr = (uintmax_t)va_arg(*ap, void *);
	str = ft_utoa(addr, 16);
	awidth = ft_strlen(str) + 2;
	if (info->width > awidth)
	{
		if (!(info->flags & FLG_MINUS))
			ft_putnchar(' ', info->width - awidth);
		ft_putstr("0x");
		ft_putstr(str);
		free(str);
		if (info->flags & FLG_MINUS)
			ft_putnchar(' ', info->width - awidth);
		return (info->width);
	}
	ft_putstr("0x");
	ft_putstr(str);
	free(str);
	return (awidth);
}
