/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:27:23 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/11 19:33:11 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"

/*
** Writes up to num characters from the string pointed by str to the
** standard output (STDOUT_FILENO). On success the number of characters
** written is returned. If a writing error occurs -1 is returned.
*/

int		ft_putnstr(char *str, int num)
{
	int		len;

	len = ft_strlen(str);
	if (num < len)
		len = num;
	return (write(STDOUT_FILENO, str, len));
}
