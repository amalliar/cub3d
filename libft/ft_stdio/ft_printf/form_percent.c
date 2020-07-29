/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 06:42:37 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/18 06:24:31 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_stdio.h"

int		form_percent(t_printf_info *info, va_list *ap)
{
	char	pchar;

	(void)ap;
	if (info->width > 1)
	{
		pchar = (info->flags & FLG_ZERO) ? '0' : ' ';
		if (!(info->flags & FLG_MINUS))
			ft_putnchar(pchar, info->width - 1);
		ft_putchar('%');
		if (info->flags & FLG_MINUS)
			ft_putnchar(pchar, info->width - 1);
		return (info->width);
	}
	ft_putchar('%');
	return (1);
}
