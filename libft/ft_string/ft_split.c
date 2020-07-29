/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 23:06:02 by amalliar          #+#    #+#             */
/*   Updated: 2020/05/24 09:21:02 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Allocates (with malloc) and returns an array of strings
** obtained by splitting 'str' using the character 'c' as
** a delimiter. The array must be ended by a NULL pointer.
*/

static size_t	get_word_count(const char *str, char c)
{
	char		*sep;
	size_t		count;

	count = 0;
	while (c != '\0' && (sep = ft_strchr(str, c)) != NULL)
	{
		if (sep - str != 0)
			++count;
		str = sep + 1;
	}
	return ((*str == '\0') ? count : count + 1);
}

static int		add_last_word(const char *str, char **word_tab, size_t i)
{
	size_t		word_len;

	word_len = ft_strlen(str);
	if (!(word_tab[i] = (char *)malloc(word_len + 1)))
		return (1);
	ft_memcpy(word_tab[i], str, word_len + 1);
	return (0);
}

static char		**clear_tab(char **word_tab)
{
	size_t		i;

	i = 0;
	while (word_tab[i] != NULL)
	{
		free(word_tab[i]);
		++i;
	}
	free(word_tab);
	return (NULL);
}

char			**ft_split(const char *str, char c)
{
	char		*sep;
	char		**word_tab;
	size_t		word_count;
	size_t		i;

	if (str == NULL || (i = 0))
		return (NULL);
	word_count = get_word_count(str, c);
	if (!(word_tab = (char **)malloc((word_count + 1) * sizeof(char *))))
		return (NULL);
	word_tab[word_count] = NULL;
	while (c != '\0' && (sep = ft_strchr(str, c)) != NULL)
	{
		if (sep - str != 0)
		{
			if (!(word_tab[i] = (char *)malloc(sep - str + 1)))
				return (clear_tab(word_tab));
			ft_memcpy(word_tab[i], str, sep - str);
			word_tab[i++][sep - str] = '\0';
		}
		str = sep + 1;
	}
	if (i < word_count && add_last_word(str, word_tab, i) != 0)
		return (clear_tab(word_tab));
	return (word_tab);
}
