/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 23:55:17 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/13 19:26:10 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

/*
** Writes num characters to the standard output (stdout). On success, the
** number of characters written is returned. If a writing error occurs -1 is
** returned.
*/

int		ft_putnchar(int c, int num)
{
	int		ret;

	ret = num;
	while (num > 0)
	{
		if (write(STDOUT_FILENO, &c, 1) == -1)
			return (-1);
		--num;
	}
	return (ret);
}
