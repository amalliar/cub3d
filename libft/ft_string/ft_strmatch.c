/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:08:03 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 19:21:04 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Checks whether the string str can match exp.
** For now only the asterisk '*' is supported.
*/

int		ft_strmatch(char *exp, char *str)
{
	while (*str)
	{
		if (*exp == '*')
		{
			while (*exp == '*')
				exp++;
			if (!*exp)
				return (1);
			while (*str)
				if (ft_strmatch(str++, exp))
					return (1);
			return (0);
		}
		else if (*str != *exp)
			return (0);
		str++;
		exp++;
	}
	while (*exp == '*')
		exp++;
	return (!*exp);
}
