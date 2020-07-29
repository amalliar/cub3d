/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:19:35 by amalliar          #+#    #+#             */
/*   Updated: 2020/06/03 19:49:00 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

/*
** Outputs the integer 'num' to the given file descriptor. On success
** the number of characters written is returned. If a writing error
** occurs -1 is returned.
*/

int		ft_putnbr_fd(int num, int fd)
{
	long long	llnum;
	short		digits;
	char		beg[16];
	char		*end;

	llnum = num;
	digits = (num == 0) ? 1 : 0;
	while (num != 0)
	{
		++digits;
		num /= 10;
	}
	*beg = (llnum == 0) ? '0' : '-';
	end = beg + (llnum < 0) + digits;
	num = end - beg;
	*end-- = '\0';
	if (llnum < 0)
		llnum = -llnum;
	while (llnum != 0)
	{
		*end-- = llnum % 10 + '0';
		llnum /= 10;
	}
	return (write(fd, beg, num));
}
