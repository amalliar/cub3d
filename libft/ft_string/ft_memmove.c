/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 20:29:48 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:20:26 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

typedef unsigned long	t_longword;

/*
** The ft_memmove() function copies num bytes from memory area src to
** memory area dest. The memory areas may overlap: copying takes place
** as though the bytes in src are first copied into a temporary array
** that does not overlap src or dest, and the bytes are then copied
** from the temporary array to dest.
*/

static inline void		byte_copy_bwd(t_longword *dest, t_longword *src, \
							size_t *num)
{
	--*dest;
	--*src;
	--*num;
	((unsigned char *)*dest)[0] = ((unsigned char *)*src)[0];
}

static inline void		word_copy_bwd(t_longword *dest, t_longword *src, \
							size_t *num)
{
	*dest -= sizeof(t_longword);
	*src -= sizeof(t_longword);
	*num -= sizeof(t_longword);
	((t_longword *)*dest)[0] = ((t_longword *)*src)[0];
}

void					*ft_memmove(void *dest, const void *src, size_t num)
{
	t_longword		pdest;
	t_longword		psrc;

	if (dest == src)
		return (dest);
	pdest = (t_longword)dest;
	psrc = (t_longword)src;
	if (pdest - psrc >= num)
		ft_memcpy(dest, src, num);
	else
	{
		pdest += num;
		psrc += num;
		if (num >= sizeof(t_longword))
		{
			while (pdest % sizeof(t_longword) != 0)
				byte_copy_bwd(&pdest, &psrc, &num);
			while (num >= sizeof(t_longword))
				word_copy_bwd(&pdest, &psrc, &num);
		}
		while (num != 0)
			byte_copy_bwd(&pdest, &psrc, &num);
	}
	return (dest);
}
