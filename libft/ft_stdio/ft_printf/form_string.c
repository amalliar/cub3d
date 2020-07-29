/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 07:18:40 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/15 22:44:59 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"
#include "ft_stdio.h"

static int		wstrlen(wchar_t *wstr)
{
	int		len;

	len = 0;
	while (*wstr != L'\0')
	{
		++len;
		++wstr;
	}
	return (len);
}

static int		putnwstr(wchar_t *wstr, int num)
{
	int		done;

	done = 0;
	while (*wstr != L'\0' && num > 0)
	{
		write(STDOUT_FILENO, wstr, 1);
		--num;
		++done;
		++wstr;
	}
	return (done);
}

static int		type_wide(t_printf_info *info, wchar_t *wstr)
{
	char	pchar;
	int		len;
	int		done;

	pchar = (info->flags & FLG_ZERO) ? '0' : ' ';
	len = (wstr == NULL) ? 6 : wstrlen(wstr);
	if (info->precision >= 0 && info->precision < len)
		len = info->precision;
	done = 0;
	if (info->flags & FLG_MINUS)
		done += (wstr == NULL) ? ft_putnstr("(null)", len) : \
			putnwstr(wstr, len);
	if (info->width > len)
		done += ft_putnchar(pchar, info->width - len);
	if (!(info->flags & FLG_MINUS))
		done += (wstr == NULL) ? ft_putnstr("(null)", len) : \
			putnwstr(wstr, len);
	return (done);
}

static int		type_regular(t_printf_info *info, char *str)
{
	char	pchar;
	int		len;
	int		done;

	pchar = (info->flags & FLG_ZERO) ? '0' : ' ';
	len = (str == NULL) ? 6 : ft_strlen(str);
	if (info->precision >= 0 && info->precision < len)
		len = info->precision;
	done = 0;
	if (info->flags & FLG_MINUS)
		done += (str == NULL) ? ft_putnstr("(null)", len) : \
			ft_putnstr(str, len);
	if (info->width > len)
		done += ft_putnchar(pchar, info->width - len);
	if (!(info->flags & FLG_MINUS))
		done += (str == NULL) ? ft_putnstr("(null)", len) : \
			ft_putnstr(str, len);
	return (done);
}

int				form_string(t_printf_info *info, va_list *ap)
{
	if (!ft_strcmp(info->length, "l"))
		return (type_wide(info, va_arg(*ap, wchar_t *)));
	else
		return (type_regular(info, va_arg(*ap, char *)));
}
