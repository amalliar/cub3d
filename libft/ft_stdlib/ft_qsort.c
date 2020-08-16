/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 20:55:47 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/15 21:29:00 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"

static void		swap(t_qsort_data *qd, int first, int second)
{
	void	*pfirst;
	void	*psecond;

	pfirst = qd->base + first * qd->size;
	psecond = qd->base + second * qd->size;
	ft_memcpy(qd->buff, pfirst, qd->size);
	ft_memcpy(pfirst, psecond, qd->size);
	ft_memcpy(psecond, qd->buff, qd->size);
}

static void		qsort_core(t_qsort_data *qd, int left, int right)
{
	int		last;
	int		i;

	if (left >= right)
		return ;
	swap(qd, left, (left + right) / 2);
	last = left;
	i = left + 1;
	while (i <= right)
	{
		if (qd->compar(qd->base + i * qd->size, \
			qd->base + left * qd->size) < 0)
			swap(qd, i, ++last);
		i++;
	}
	swap(qd, left, last);
	qsort_core(qd, left, last - 1);
	qsort_core(qd, last + 1, right);
}

void			ft_qsort(void *base, size_t num, size_t size, \
					int (*compar)(const void *, const void *))
{
	t_qsort_data	qd;

	qd.base = base;
	qd.size = size;
	qd.compar = compar;
	if (!(qd.buff = malloc(size)))
		return ;
	qsort_core(&qd, 0, num - 1);
	free(qd.buff);
}
