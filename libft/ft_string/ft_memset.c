/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:00:28 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:20:45 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

typedef unsigned long	t_longword;

/*
** Sets the first num bytes of the block of memory pointed by
** ptr to the specified value c (interpreted as an unsigned char).
*/

static inline void		byte_copy_fwd(t_longword *dest, t_longword block, \
							size_t *num)
{
	((unsigned char *)*dest)[0] = block;
	++*dest;
	--*num;
}

static inline void		word_copy_fwd(t_longword *dest, t_longword block, \
							size_t *num)
{
	((t_longword *)*dest)[0] = block;
	*dest += sizeof(t_longword);
	*num -= sizeof(t_longword);
}

static inline void		page_copy_fwd(t_longword *dest, t_longword block, \
							size_t *num)
{
	((t_longword *)*dest)[0] = block;
	((t_longword *)*dest)[1] = block;
	((t_longword *)*dest)[2] = block;
	((t_longword *)*dest)[3] = block;
	((t_longword *)*dest)[4] = block;
	((t_longword *)*dest)[5] = block;
	((t_longword *)*dest)[6] = block;
	((t_longword *)*dest)[7] = block;
	*dest += 8 * sizeof(t_longword);
	*num -= 8 * sizeof(t_longword);
}

void					*ft_memset(void *ptr, int c, size_t num)
{
	t_longword		dest;
	t_longword		block;

	dest = (t_longword)ptr;
	block = (unsigned char)c;
	block |= block << 8;
	block |= block << 16;
	block |= (block << 16) << 16;
	if (num >= sizeof(t_longword))
	{
		while (dest % sizeof(t_longword) != 0)
			byte_copy_fwd(&dest, block, &num);
		while (num >= 8 * sizeof(t_longword))
			page_copy_fwd(&dest, block, &num);
		while (num >= sizeof(t_longword))
			word_copy_fwd(&dest, block, &num);
	}
	while (num != 0)
		byte_copy_fwd(&dest, block, &num);
	return (ptr);
}
