/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 14:52:18 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:22:09 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

typedef unsigned long	t_longword;

/*
** Returns a pointer to the first occurrence of character
** in the C string str.
*/

static inline void		init_magic(t_longword *himagic, t_longword *lomagic, \
							t_longword *chmagic, unsigned char c)
{
	*himagic = 0x80808080;
	*lomagic = 0x01010101;
	*chmagic = c;
	*chmagic |= *chmagic << 8;
	*chmagic |= *chmagic << 16;
	if (sizeof(t_longword) > 4)
	{
		*himagic |= (*himagic << 16) << 16;
		*lomagic |= (*lomagic << 16) << 16;
		*chmagic |= (*chmagic << 16) << 16;
	}
}

/*
**           byte1     byte2          byte8(4)
**
** lomagic:  00000001  00000001  ...  00000001
**
** himagic:  10000000  10000000  ...  10000000
**
** chmagic:  01000001  01000001  ...  01000001
** (for c == 'A')
*/

static inline int		test_longword(const char **char_ptr, char c)
{
	unsigned	i;

	i = 0;
	while (i < sizeof(t_longword))
	{
		if ((*char_ptr)[i] == c)
		{
			*char_ptr += i;
			return (1);
		}
		if ((*char_ptr)[i] == '\0')
		{
			*char_ptr = NULL;
			return (1);
		}
		++i;
	}
	return (0);
}

char					*ft_strchr(const char *str, int c)
{
	const t_longword	*longword_ptr;
	t_longword			longword;
	t_longword			himagic;
	t_longword			lomagic;
	t_longword			chmagic;

	while ((size_t)str % sizeof(t_longword) != 0)
	{
		if (*str == (char)c || *str == '\0')
			return ((*str == (char)c) ? (char *)str : NULL);
		++str;
	}
	longword_ptr = (const t_longword *)str;
	init_magic(&himagic, &lomagic, &chmagic, c);
	while (1)
	{
		longword = *longword_ptr++;
		if (((longword - lomagic) & ~longword & himagic) != 0 || \
			(((longword ^ chmagic) - lomagic) & ~longword & himagic) != 0)
		{
			str = (char *)(longword_ptr - 1);
			if (test_longword(&str, c))
				return ((char *)str);
		}
	}
}
