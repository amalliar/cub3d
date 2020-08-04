/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:49:25 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/04 18:50:43 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"

/*
** Writes up to num characters from the string pointed by str to the
** file descriptor fd. On success the number of characters written is
** returned. If a writing error occurs -1 is returned.
*/

int		ft_putnstr_fd(char *str, int fd, int num)
{
	int		len;

	len = ft_strlen(str);
	if (num < len)
		len = num;
	return (write(fd, str, len));
}
