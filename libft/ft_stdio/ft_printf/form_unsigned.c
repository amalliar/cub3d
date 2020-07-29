/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_unsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 07:14:03 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/20 21:35:53 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "form_unsigned.h"

static int		get_num_base(t_printf_info *info)
{
	if (info->form == 'u')
		return (10);
	else if (info->form == 'o')
		return (8);
	else if ((info->form == 'x') || (info->form == 'X'))
		return (16);
	return (-1);
}

static int		get_base_len(t_printf_info *info, char *str)
{
	if ((info->form == 'o') && (info->flags & FLG_HASH) && \
		*str != '0')
		return (1);
	if ((info->form == 'x' || info->form == 'X') && \
		(info->flags & FLG_HASH) && *str != '0')
		return (2);
	return (0);
}

static void		bypass_25_line_limit(char *str, int *nlen, \
					int *padding, t_printf_info *info)
{
	*nlen = ft_strlen(str);
	*padding = (info->precision > *nlen) ? info->precision - *nlen : 0;
	if (*padding != 0 && info->form == 'o')
		info->flags &= ~FLG_HASH;
}

static int		type_regular(t_printf_info *info, uintmax_t num)
{
	char	*str;
	char	pchar;
	int		padding;
	int		nlen;
	int		nwidth;

	if (info->precision == 0 && num == 0 && \
		(info->form != 'o' || !(info->flags & FLG_HASH)))
		return (ft_putnchar(' ', info->width));
	str = ft_utoa(num, get_num_base(info));
	bypass_25_line_limit(str, &nlen, &padding, info);
	nwidth = get_base_len(info, str) + nlen + padding;
	pchar = ((info->flags & FLG_ZERO) && (info->precision < 0)) ? '0' : ' ';
	if (pchar == '0' && (info->flags & FLG_HASH) && num != 0)
		print_num_base(info);
	if (info->width > nwidth && !(info->flags & FLG_MINUS))
		ft_putnchar(pchar, info->width - nwidth);
	if (pchar == ' ' && (info->flags & FLG_HASH) && num != 0)
		print_num_base(info);
	ft_putnchar('0', padding);
	ft_putstr((info->form == 'X') ? ft_strtoupper(str) : str);
	free(str);
	if ((info->width > nwidth) && (info->flags & FLG_MINUS))
		ft_putnchar(pchar, info->width - nwidth);
	return ((info->width > nwidth) ? info->width : nwidth);
}

int				form_unsigned(t_printf_info *info, va_list *ap)
{
	if (!ft_strcmp(info->length, ""))
		return (type_regular(info, va_arg(*ap, unsigned int)));
	else if (!ft_strcmp(info->length, "hh"))
		return (type_regular(info, (unsigned char)va_arg(*ap, unsigned int)));
	else if (!ft_strcmp(info->length, "h"))
		return (type_regular(info, \
		(unsigned short int)va_arg(*ap, unsigned int)));
	else if (!ft_strcmp(info->length, "l"))
		return (type_regular(info, va_arg(*ap, unsigned long int)));
	else if (!ft_strcmp(info->length, "ll"))
		return (type_regular(info, va_arg(*ap, unsigned long long)));
	else if (!ft_strcmp(info->length, "j"))
		return (type_regular(info, va_arg(*ap, uintmax_t)));
	else if (!ft_strcmp(info->length, "z"))
		return (type_regular(info, va_arg(*ap, size_t)));
	else if (!ft_strcmp(info->length, "t"))
		return (type_regular(info, va_arg(*ap, ptrdiff_t)));
	return (0);
}
