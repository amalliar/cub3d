/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 06:47:14 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/10 19:36:08 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"

int		form_number(t_printf_info *info, va_list *ap, int done)
{
	if (!ft_strcmp(info->length, ""))
		*(va_arg(*ap, int *)) = done;
	else if (!ft_strcmp(info->length, "hh"))
		*(va_arg(*ap, signed char *)) = (signed char)done;
	else if (!ft_strcmp(info->length, "h"))
		*(va_arg(*ap, short int *)) = (short int)done;
	else if (!ft_strcmp(info->length, "l"))
		*(va_arg(*ap, long int *)) = (long int)done;
	else if (!ft_strcmp(info->length, "ll"))
		*(va_arg(*ap, long long int *)) = (long long int)done;
	else if (!ft_strcmp(info->length, "j"))
		*(va_arg(*ap, intmax_t *)) = (intmax_t)done;
	else if (!ft_strcmp(info->length, "z"))
		*(va_arg(*ap, size_t *)) = (size_t)done;
	else if (!ft_strcmp(info->length, "t"))
		*(va_arg(*ap, ptrdiff_t *)) = (ptrdiff_t)done;
	return (0);
}
