/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:13:03 by amalliar          #+#    #+#             */
/*   Updated: 2020/06/03 19:47:19 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"

/*
** Outputs the C-string 'str' to the given file descriptor, followed by a
** newline. On success the number of characters written is returned. If a
** writing error occurs -1 is returned.
*/

int		ft_putendl_fd(char *str, int fd)
{
	int		ret;

	if (str == NULL)
		return (-1);
	if ((ret = write(fd, str, ft_strlen(str))) == -1)
		return (-1);
	if (write(fd, "\n", 1) == -1)
		return (-1);
	return (ret + 1);
}
