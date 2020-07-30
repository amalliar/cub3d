/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 07:12:41 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/30 18:27:43 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDLIB_H
# define FT_STDLIB_H
# include <limits.h>
# include <float.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct		s_ftoa_info
{
	long double		num;
	unsigned		prec;
	char			*buf;
	size_t			len;
	double			diff;
	bool			negative;
	int				whole;
	double			tmp;
	unsigned long	frac;
	unsigned int	count;

}					t_ftoa_info;

char				*ft_ftoa(long double num, unsigned prec);
char				*ft_itoa(intmax_t num, int base);
char				*ft_utoa(uintmax_t num, int base);
int					ft_abs(int num);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t num, size_t size);

#endif
