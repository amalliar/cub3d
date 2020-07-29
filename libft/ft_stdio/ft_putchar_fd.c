/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:22:14 by amalliar          #+#    #+#             */
/*   Updated: 2020/06/03 20:01:37 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

/*
** Writes a character to the given file descriptor. On success, the
** character written is returned. If a writing error occurs -1 is
** returned.
*/

int		ft_putchar_fd(int c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (c);
}
