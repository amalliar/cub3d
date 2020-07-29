/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:04:33 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/13 18:49:31 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"

/*
** Outputs the C-string 'str' to the given file descriptor. On success
** the number of characters written is returned. If a writing error
** occurs -1 is returned.
*/

int		ft_putstr_fd(char *str, int fd)
{
	int		ret;

	if (str == NULL)
		return (-1);
	if ((ret = write(fd, str, ft_strlen(str))) == -1)
		return (-1);
	return (ret);
}
