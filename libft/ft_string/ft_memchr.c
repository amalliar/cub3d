/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 13:19:15 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:19:25 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

typedef unsigned long	t_longword;

/*
** Searches within the first num bytes of the block of memory pointed by
** ptr for the first occurrence of c (interpreted as an unsigned char),
** and returns a pointer to it.
*/

static inline void		init_magic(t_longword *lomagic, \
							t_longword *chmagic, int c)
{
	*lomagic = 0x01010101;
	*chmagic = c;
	*chmagic |= *chmagic << 8;
	*chmagic |= *chmagic << 16;
	if (sizeof(t_longword) > 4)
	{
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

static inline void		test_longwords(const t_longword **longword_ptr, \
							size_t *num, t_longword lomagic, t_longword chmagic)
{
	t_longword		longword;
	t_longword		himagic;

	himagic = 0x80808080;
	if (sizeof(t_longword) > 4)
		himagic |= (himagic << 16) << 16;
	while (*num >= sizeof(t_longword))
	{
		longword = **longword_ptr ^ chmagic;
		if (((longword - lomagic) & ~longword & himagic) != 0)
			break ;
		++*longword_ptr;
		*num -= sizeof(t_longword);
	}
}

void					*ft_memchr(const void *ptr, int c, size_t num)
{
	const unsigned char		*char_ptr;
	const t_longword		*longword_ptr;
	t_longword				lomagic;
	t_longword				chmagic;

	c = (unsigned char)c;
	char_ptr = (const unsigned char *)ptr;
	while (num != 0 && (size_t)char_ptr % sizeof(t_longword) != 0)
	{
		if (*char_ptr == c)
			return ((void *)char_ptr);
		++char_ptr;
		--num;
	}
	longword_ptr = (const t_longword *)char_ptr;
	init_magic(&lomagic, &chmagic, c);
	test_longwords(&longword_ptr, &num, lomagic, chmagic);
	char_ptr = (const unsigned char *)longword_ptr;
	while (num-- != 0)
	{
		if (*char_ptr == c)
			return ((void *)char_ptr);
		++char_ptr;
	}
	return (NULL);
}
