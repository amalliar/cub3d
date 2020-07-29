/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_unsigned_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 21:58:18 by amalliar          #+#    #+#             */
/*   Updated: 2020/07/18 03:06:08 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "form_unsigned.h"

void	print_num_base(t_printf_info *info)
{
	if (info->form == 'o')
		ft_putstr("0");
	else if (info->form == 'x')
		ft_putstr("0x");
	else if (info->form == 'X')
		ft_putstr("0X");
}
