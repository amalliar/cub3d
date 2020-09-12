/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 07:19:51 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/12 19:13:59 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H
# include <stddef.h>
# include <stdlib.h>

char		**ft_split(const char *str, char c);
char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *str);
char		*ft_strjoin(const char *str1, const char *str2);
char		*ft_strmapi(const char *str, char (*func)(unsigned int, char));
char		*ft_strstr(const char *big, const char *little);
char		*ft_strnstr(const char *big, const char *little, size_t num);
char		*ft_strrchr(const char *str, int c);
char		*ft_strrev(char *str);
char		*ft_strtolower(char *str);
char		*ft_strtoupper(char *str);
char		*ft_strtrim(const char *str, const char *set);
char		*ft_substr(const char *str, unsigned int start, size_t num);
int			ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
int			ft_strcmp(const char *str1, const char *str2);
int			ft_strisnumeric(char *str);
int			ft_strisspace(char *str);
int			ft_strmatch(char *exp, char *str);
int			ft_strncmp(const char *str1, const char *str2, size_t num);
size_t		ft_strlcat(char *dest, const char *src, size_t num);
size_t		ft_strlcpy(char *dest, const char *src, size_t num);
size_t		ft_strlen(const char *str);
void		*ft_memccpy(void *dest, const void *src, int c, size_t num);
void		*ft_memchr(const void *ptr, int c, size_t num);
void		*ft_memcpy(void *dest, const void *src, size_t num);
void		*ft_memmove(void *dest, const void *src, size_t num);
void		*ft_memset(void *ptr, int c, size_t num);

#endif
