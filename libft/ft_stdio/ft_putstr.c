/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:04:33 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/18 06:18:08 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"

/*
** Outputs the C-string 'str' to the standard output. On success
** the number of characters written is returned. If a writing error
** occurs -1 is returned.
*/

int		ft_putstr(char *str)
{
	int		ret;

	if ((ret = write(STDOUT_FILENO, str, ft_strlen(str))) == -1)
		return (-1);
	return (ret);
}
