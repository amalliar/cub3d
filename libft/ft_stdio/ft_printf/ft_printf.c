/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 23:29:29 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/18 03:43:40 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"

/*
** Writes the C string pointed by format to the standard output (stdout).
** If format includes format specifiers (subsequences beginning with %),
** the additional arguments following format are formatted and inserted
** in the resulting string replacing their respective specifiers.
*/

static void		init_printf_info(t_printf_info *info)
{
	info->flags = 0;
	info->width = INT_MIN;
	info->precision = INT_MIN;
	ft_memset(info->length, 0, 3);
	info->form = 0;
}

static int		parse_format(const char **format, va_list *ap, int done)
{
	t_printf_info	info;

	init_printf_info(&info);
	parse_flags(format, &info);
	parse_width(format, &info, ap);
	parse_precision(format, &info, ap);
	parse_length(format, &info);
	return (parse_form(format, &info, ap, done));
}

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	int			done;
	char		*next_spec;

	va_start(ap, format);
	done = 0;
	while (*format != '\0')
	{
		next_spec = ft_strchr(format, '%');
		if (next_spec != NULL)
		{
			done += write(STDOUT_FILENO, format, next_spec - format);
			format = next_spec + 1;
			if (*format != '\0')
				done += parse_format(&format, &ap, done);
			continue ;
		}
		done += write(STDOUT_FILENO, format, ft_strlen(format));
		break ;
	}
	va_end(ap);
	return (done);
}
