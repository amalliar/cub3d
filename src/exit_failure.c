/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_failure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:32:42 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/13 19:22:06 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_stdio.h"
#include "ft_string.h"

static void		parse_format(char **format, va_list *ap)
{
	if (**format == 's')
	{
		ft_putstr_fd(va_arg(*ap, char *), STDERR_FILENO);
		++*format;
	}
	else if (**format == 'c')
	{
		ft_putchar_fd((char)va_arg(*ap, int), STDERR_FILENO);
		++*format;
	}
}

void			exit_failure(char *format, ...)
{
	va_list		ap;
	char		*next_spec;

	va_start(ap, format);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	while (*format)
	{
		if ((next_spec = ft_strchr(format, '%')) != NULL)
		{
			ft_putnstr_fd(format, STDERR_FILENO, next_spec - format);
			format = next_spec + 1;
			parse_format(&format, &ap);
			continue ;
		}
		ft_putstr_fd(format, STDERR_FILENO);
		break ;
	}
	va_end(ap);
	exit(EXIT_FAILURE);
}
