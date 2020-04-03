/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:15:07 by gbudau            #+#    #+#             */
/*   Updated: 2020/04/01 16:19:45 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	const char	*e;

	e = s;
	while (*e)
		e++;
	return (e - s);
}

char	*gnl_strcpy(char *dst, const char *src)
{
	char	*tmp;

	tmp = dst;
	while (*src)
		*tmp++ = *src++;
	*tmp = '\0';
	return (tmp);
}

char	*gnl_strdup(const char *s1)
{
	char	*ret;

	if ((ret = malloc(gnl_strlen(s1) + 1)) == NULL)
		return (NULL);
	gnl_strcpy(ret, s1);
	return (ret);
}

char	*gnl_strchr(const char *s, int c)
{
	unsigned char	ch;

	ch = c;
	while (s)
	{
		if (*s == ch)
			return ((char *)s);
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return (NULL);
}

char	*gnl_strjoin_free(char *s1, char const *s2)
{
	char	*ret;
	size_t	l1;
	size_t	l2;

	if (s1 == NULL)
		return (NULL);
	l1 = gnl_strlen(s1);
	l2 = gnl_strlen(s2);
	if (!(ret = malloc(l1 + l2 + 1)))
		return (NULL);
	gnl_strcpy(ret, s1);
	gnl_strcpy(ret + l1, s2);
	free(s1);
	s1 = NULL;
	return (ret);
}
