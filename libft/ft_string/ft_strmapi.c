/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 21:56:58 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:25:05 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Applies the function func() to each character of the string
** str to create a new string (with malloc) resulting from
** successive applications of func().
*/

char	*ft_strmapi(const char *str, char (*func)(unsigned int, char))
{
	char	*map;
	size_t	len;
	size_t	i;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if (!(map = (char *)malloc(len + 1)))
		return (NULL);
	map[len] = '\0';
	i = 0;
	while (len - i >= 4)
	{
		map[i] = func(i, str[i]);
		map[i + 1] = func(i + 1, str[i + 1]);
		map[i + 2] = func(i + 2, str[i + 2]);
		map[i + 3] = func(i + 3, str[i + 3]);
		i += 4;
	}
	while (i < len)
	{
		map[i] = func(i, str[i]);
		++i;
	}
	return (map);
}
