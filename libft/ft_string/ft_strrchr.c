/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 18:21:56 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:26:32 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Returns a pointer to the last occurrence of character c
** in the C string str.
*/

char	*ft_strrchr(const char *str, int c)
{
	char	*found;
	char	*ptr;

	if (c == '\0')
		return (ft_strchr((char *)str, '\0'));
	found = NULL;
	while ((ptr = ft_strchr((char *)str, c)) != NULL)
	{
		found = ptr;
		str = ptr + 1;
	}
	return (found);
}
