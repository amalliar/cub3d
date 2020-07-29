/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 17:33:53 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:25:35 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Compares up to num characters of the C string str1 to those
** of the C string str2.
*/

int		ft_strncmp(const char *str1, const char *str2, size_t num)
{
	while (num >= 4)
	{
		if (str1[0] == '\0' || str1[0] != str2[0])
			return ((unsigned char)str1[0] - (unsigned char)str2[0]);
		if (str1[1] == '\0' || str1[1] != str2[1])
			return ((unsigned char)str1[1] - (unsigned char)str2[1]);
		if (str1[2] == '\0' || str1[2] != str2[2])
			return ((unsigned char)str1[2] - (unsigned char)str2[2]);
		if (str1[3] == '\0' || str1[3] != str2[3])
			return ((unsigned char)str1[3] - (unsigned char)str2[3]);
		str1 += 4;
		str2 += 4;
		num -= 4;
	}
	while (num != 0)
	{
		if (str1[0] == '\0' || str1[0] != str2[0])
			return ((unsigned char)str1[0] - (unsigned char)str2[0]);
		++str1;
		++str2;
		--num;
	}
	return (0);
}
