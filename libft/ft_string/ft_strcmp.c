/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 19:52:39 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/10 19:58:42 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** This function starts comparing the first character of each string.
** If they are equal to each other, it continues with the following pairs
** until the characters differ or until a terminating null-character is reached.
*/

int		ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str1 == *str2)
	{
		++str1;
		++str2;
	}
	return (*str1 - *str2);
}
