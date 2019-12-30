/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:15:07 by gbudau            #+#    #+#             */
/*   Updated: 2019/12/23 23:58:54 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (dst == src)
		return (dst);
	while (n--)
		*d++ = *s++;
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s1);
	if (!(ret = malloc(len + 1)))
		return (NULL);
	ft_memcpy(ret, s1, len + 1);
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	const char		*p;

	p = s;
	if (p)
	{
		while (*p)
		{
			if (*p == (const char)c)
				return ((char *)p);
			p++;
		}
		if (*p == (const char)c)
			return ((char *)p);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
		i++;
	j = 0;
	while (s2[j] != '\0')
		j++;
	if (!(ret = malloc(i + j + 1)))
		return (NULL);
	ret[i + j] = '\0';
	while (j-- != 0)
		ret[i + j] = s2[j];
	while (i-- != 0)
		ret[i] = s1[i];
	return (ret);
}
