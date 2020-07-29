/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 23:50:32 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/19 02:04:34 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#define FTOA_BUFFER_SIZE 64U

static void		init_vars(t_ftoa_info *info, long double num, \
					unsigned prec)
{
	info->num = num;
	info->prec = prec;
	info->len = 0U;
	info->diff = 0.0;
	info->negative = false;
	if (info->num < 0)
	{
		info->negative = true;
		info->num = 0 - info->num;
	}
}

static void		stage_one(t_ftoa_info *info)
{
	static const double	pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, \
	10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, \
	10000000000000, 100000000000000, 1000000000000000, 10000000000000000};

	info->whole = (int)info->num;
	info->tmp = (info->num - info->whole) * pow10[info->prec];
	info->frac = (unsigned long)info->tmp;
	info->diff = info->tmp - info->frac;
	if (info->diff > 0.5)
	{
		++info->frac;
		if (info->frac >= pow10[info->prec])
		{
			info->frac = 0;
			++info->whole;
		}
	}
	else if (info->diff == 0.5)
		++info->frac;
}

static void		stage_two(t_ftoa_info *info)
{
	if (info->prec == 0U)
	{
		info->diff = info->num - (double)info->whole;
		if ((info->diff >= 0.5) && (info->whole & 1))
			++info->whole;
	}
	else
	{
		info->count = info->prec;
		while (info->len < FTOA_BUFFER_SIZE)
		{
			--info->count;
			(info->buf)[info->len++] = (char)(48U + (info->frac % 10U));
			if (!(info->frac /= 10U))
				break ;
		}
		while ((info->len < FTOA_BUFFER_SIZE) && (info->count-- > 0U))
			(info->buf)[info->len++] = '0';
		if (info->len < FTOA_BUFFER_SIZE)
			(info->buf)[info->len++] = '.';
	}
}

static void		stage_three(t_ftoa_info *info)
{
	while (info->len < FTOA_BUFFER_SIZE)
	{
		(info->buf)[info->len++] = (char)(48 + (info->whole % 10));
		if (!(info->whole /= 10))
			break ;
	}
	if (info->len < FTOA_BUFFER_SIZE && info->negative)
		(info->buf)[info->len++] = '-';
	info->buf[info->len] = '\0';
}

char			*ft_ftoa(long double num, unsigned prec)
{
	t_ftoa_info		info;

	if (num != num)
		return (ft_strdup("nan"));
	if (num < -LDBL_MAX)
		return (ft_strdup("-inf"));
	if (num > LDBL_MAX)
		return (ft_strdup("inf"));
	init_vars(&info, num, prec);
	if (!(info.buf = (char *)malloc(FTOA_BUFFER_SIZE)))
		return (NULL);
	while ((info.len < FTOA_BUFFER_SIZE) && (info.prec > 16U))
	{
		(info.buf)[info.len++] = '0';
		info.prec--;
	}
	stage_one(&info);
	stage_two(&info);
	stage_three(&info);
	return (ft_strrev(info.buf));
}
