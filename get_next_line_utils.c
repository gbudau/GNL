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

void	ft_freeptr(char **ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	*ptr = NULL;
}

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	len;

	len = 0;
	while (s1[len] != 0)
		len++;
	if ((ret = malloc(++len)) == NULL)
		return (NULL);
	while (len--)
		ret[len] = s1[len];
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	char	ch;

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
