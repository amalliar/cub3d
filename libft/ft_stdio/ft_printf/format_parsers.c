/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parsers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 03:05:32 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/16 12:19:09 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"
#include "ft_ctype.h"
#include "form_table.h"

void	parse_flags(const char **format, t_printf_info *info)
{
	while (1)
	{
		if (**format == '-')
		{
			info->flags |= FLG_MINUS;
			info->flags &= ~FLG_ZERO;
		}
		else if (**format == '+')
			info->flags |= FLG_PLUS;
		else if (**format == ' ')
			info->flags |= FLG_SPACE;
		else if (**format == '#')
			info->flags |= FLG_HASH;
		else if (**format == '0' && !(info->flags & FLG_MINUS))
			info->flags |= FLG_ZERO;
		else
			break ;
		++*format;
	}
}

void	parse_width(const char **format, t_printf_info *info, \
			va_list *ap)
{
	int		width;

	if (**format == '*')
	{
		info->width = va_arg(*ap, int);
		if (info->width < 0)
		{
			info->width *= -1;
			info->flags |= FLG_MINUS;
			info->flags &= ~FLG_ZERO;
		}
		++*format;
		return ;
	}
	width = 0;
	while (ft_isdigit(**format))
	{
		width = width * 10 + **format - '0';
		++*format;
	}
	info->width = width;
}

void	parse_precision(const char **format, t_printf_info *info, \
			va_list *ap)
{
	int		precision;

	if (**format != '.')
		return ;
	++*format;
	if (**format == '*')
	{
		info->precision = va_arg(*ap, int);
		++*format;
		return ;
	}
	precision = 0;
	while (ft_isdigit(**format))
	{
		precision = precision * 10 + **format - '0';
		++*format;
	}
	info->precision = precision;
}

void	parse_length(const char **format, t_printf_info *info)
{
	if (**format && (ft_strchr("hljztL", **format) != NULL))
	{
		(info->length)[0] = **format;
		++*format;
		if (**format && (ft_strchr("hl", **format) != NULL))
		{
			(info->length)[1] = **format;
			++*format;
		}
	}
}

int		parse_form(const char **format, t_printf_info *info, \
			va_list *ap, int done)
{
	static char		*specs = "%diuoxXfFeEgGaAcspn";
	char			*ptr;

	if (**format && ((ptr = ft_strchr(specs, **format)) != NULL))
	{
		info->form = **format;
		++*format;
		if (info->form == 'n')
			return (form_number(info, ap, done));
		return ((g_form_table[ptr - specs])(info, ap));
	}
	return (0);
}
