/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 20:42:35 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/05 20:46:46 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"

/*
** Checks whether c is one of the following white-space characters:
** '\t', '\n', '\v', '\f', '\r', ' '
*/

int		ft_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}
