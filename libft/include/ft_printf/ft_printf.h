/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 04:40:34 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/20 22:16:41 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define FLG_MINUS	0b00000001
# define FLG_PLUS	0b00000010
# define FLG_SPACE	0b00000100
# define FLG_HASH	0b00001000
# define FLG_ZERO	0b00010000
# include <stdlib.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>
# include <wchar.h>
# include <limits.h>

typedef struct		s_printf_info
{
	unsigned		flags;
	int				width;
	int				precision;
	char			length[3];
	char			form;
}					t_printf_info;

void				parse_flags(const char **format, t_printf_info *info);
void				parse_width(const char **format, t_printf_info *info, \
						va_list *ap);
void				parse_precision(const char **format, t_printf_info *info, \
						va_list *ap);
void				parse_length(const char **format, t_printf_info *info);
int					parse_form(const char **format, t_printf_info *info, \
						va_list *ap, int done);
int					form_percent(t_printf_info *info, va_list *ap);
int					form_integer(t_printf_info *info, va_list *ap);
int					form_unsigned(t_printf_info *info, va_list *ap);
int					form_float(t_printf_info *info, va_list *ap);
int					form_character(t_printf_info *info, va_list *ap);
int					form_string(t_printf_info *info, va_list *ap);
int					form_pointer(t_printf_info *info, va_list *ap);
int					form_number(t_printf_info *info, va_list *ap, int done);

#endif
