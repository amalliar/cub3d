/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:54:50 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:20:08 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

typedef unsigned long	t_longword;

/*
** Copies the values of num bytes from the location pointed to by
** src directly to the memory block pointed to by dest.
*/

static inline void		byte_copy_fwd(t_longword *dest, t_longword *src, \
							size_t *num)
{
	((unsigned char *)*dest)[0] = ((unsigned char *)*src)[0];
	++*dest;
	++*src;
	--*num;
}

static inline void		word_copy_fwd(t_longword *dest, t_longword *src, \
							size_t *num)
{
	((t_longword *)*dest)[0] = ((t_longword *)*src)[0];
	*dest += sizeof(t_longword);
	*src += sizeof(t_longword);
	*num -= sizeof(t_longword);
}

static inline void		page_copy_fwd(t_longword *dest, t_longword *src, \
							size_t *num)
{
	((t_longword *)*dest)[0] = ((t_longword *)*src)[0];
	((t_longword *)*dest)[1] = ((t_longword *)*src)[1];
	((t_longword *)*dest)[2] = ((t_longword *)*src)[2];
	((t_longword *)*dest)[3] = ((t_longword *)*src)[3];
	((t_longword *)*dest)[4] = ((t_longword *)*src)[4];
	((t_longword *)*dest)[5] = ((t_longword *)*src)[5];
	((t_longword *)*dest)[6] = ((t_longword *)*src)[6];
	((t_longword *)*dest)[7] = ((t_longword *)*src)[7];
	*dest += 8 * sizeof(t_longword);
	*src += 8 * sizeof(t_longword);
	*num -= 8 * sizeof(t_longword);
}

void					*ft_memcpy(void *dest, const void *src, size_t num)
{
	t_longword		pdest;
	t_longword		psrc;

	if (dest == src)
		return (dest);
	pdest = (t_longword)dest;
	psrc = (t_longword)src;
	if (num >= sizeof(t_longword))
	{
		while (pdest % sizeof(t_longword) != 0)
			byte_copy_fwd(&pdest, &psrc, &num);
		while (num >= 8 * sizeof(t_longword))
			page_copy_fwd(&pdest, &psrc, &num);
		while (num >= sizeof(t_longword))
			word_copy_fwd(&pdest, &psrc, &num);
	}
	while (num != 0)
		byte_copy_fwd(&pdest, &psrc, &num);
	return (dest);
}
