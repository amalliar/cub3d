/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_failure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:32:42 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/05 20:38:46 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_stdio.h"
#include "ft_string.h"

void	exit_failure(char *msg, ...)
{
	va_list		ap;
	char		*next_spec;

	va_start(ap, msg);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	while (*msg)
	{
		if ((next_spec = ft_strchr(msg, '%')) != NULL)
		{
			ft_putnstr_fd(msg, STDERR_FILENO, next_spec - msg);
			msg = next_spec + 1;
			if (*msg == 's')
			{
				++msg;
				ft_putstr_fd(va_arg(ap, char *), STDERR_FILENO);
			}
			else if (*msg == 'c')
			{
				++msg;
				ft_putchar_fd((char)va_arg(ap, int), STDERR_FILENO);
			}
			continue ;
		}
		ft_putstr_fd(msg, STDERR_FILENO);
		break ;
	}
	va_end(ap);
	exit(EXIT_FAILURE);
}
