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

static void	ft_freeptr(char **ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	*ptr = NULL;
}

static char	*ft_checkrest(char **rest, char **line)
{
	char	*next;

	next = NULL;
	if (*rest != 0)
	{
		if ((next = ft_strchr(*rest, '\n')))
		{
			*next++ = '\0';
			*line = ft_strdup(*rest);
			ft_memcpy(*rest, next, ft_strlen(next) + 1);
		}
		else
			*line = ft_strdup(*rest);
	}
	else
		*line = ft_strdup("");
	return (next);
}

char		*ft_checkbuff(char *next, char **rest, char *buff)
{
	char	*tmp;

	tmp = NULL;
	if ((next = ft_strchr(buff, '\n')))
	{
		*next++ = '\0';
		tmp = *rest;
		*rest = ft_strdup(next);
		free(tmp);
		tmp = NULL;
	}
	return (next);
}

int			ft_readbuff(int fd, char **line, char **rest, char *next)
{
	char			buff[BUFFER_SIZE + 1];
	ssize_t			br;
	char			*tmp;

	next = ft_checkrest(rest, line);
	while (next == NULL && (br = read(fd, buff, BUFFER_SIZE)))
	{
		buff[br] = '\0';
		next = ft_checkbuff(next, rest, buff);
		tmp = *line;
		if (br < 0 || !(*line = ft_strjoin(*line, buff)))
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
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static	char	*rest;
	char			*next;

	next = NULL;
	if (fd < 0 || !line || read(fd, next, 0))
		return (-1);
	return (ft_readbuff(fd, line, &rest, next));
}
