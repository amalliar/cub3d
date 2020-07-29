/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 07:21:10 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/15 17:10:29 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_TABLE_H
# define FORM_TABLE_H
# include "ft_printf.h"

static int	(*g_form_table[18])(t_printf_info *info, va_list *ap) = \
{
	form_percent,
	form_integer,
	form_integer,
	form_unsigned,
	form_unsigned,
	form_unsigned,
	form_unsigned,
	form_float,
	form_float,
	form_float,
	form_float,
	form_float,
	form_float,
	form_float,
	form_float,
	form_character,
	form_string,
	form_pointer
};

#endif
