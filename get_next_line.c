/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:15:15 by gbudau            #+#    #+#             */
/*   Updated: 2019/12/24 00:28:42 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_checkrest(char **rest, char **line, ssize_t *re)
{
	char	*next;
	ssize_t	i;

	i = -1;
	*re = 1;
	next = NULL;
	if (*rest != 0)
	{
		if ((next = ft_strchr(*rest, '\n')))
		{
			*next++ = '\0';
			*line = ft_strdup(*rest);
			while (next[++i])
				(*rest)[i] = next[i];
			(*rest)[i] = '\0';
		}
		else
			*line = ft_strdup(*rest);
	}
	else
		*line = ft_strdup("");
	if (*line == NULL)
		*re = -1;
	return (next);
}

char		*ft_checkbuff(char *next, char **rest, char *buff, ssize_t *re)
{
	char	*tmp;

	*re = 1;
	if ((next = ft_strchr(buff, '\n')))
	{
		*next++ = '\0';
		tmp = *rest;
		*rest = ft_strdup(next);
		if (*rest == NULL)
			*re = -1;
		ft_freeptr(&tmp);
	}
	return (next);
}

int			ft_readbuff(int fd, char **line, char **rest)
{
	char			buff[BUFFER_SIZE + 1];
	char			*next;
	ssize_t			re;
	char			*tmp;

	next = ft_checkrest(rest, line, &re);
	while (re > 0 && next == NULL && (re = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[re] = '\0';
		next = ft_checkbuff(next, rest, buff, &re);
		tmp = *line;
		if (re < 0 || !(*line = ft_strjoin(*line, buff)))
		{
			ft_freeptr(rest);
			ft_freeptr(&tmp);
			return (-1);
		}
		ft_freeptr(&tmp);
	}
	if (next == NULL)
	{
		ft_freeptr(rest);
		return (0);
	}
	return ((re < 0) ? -1 : 1);
}

int			get_next_line(int fd, char **line)
{
	static	char	*rest;
	char		*test;

	test = NULL;
	if (fd < 0 || !line || read(fd, test, 0))
		return (-1);
	return (ft_readbuff(fd, line, &rest));
}
