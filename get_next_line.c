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

static char	*ft_checksave(char **save, char **line, ssize_t *error)
{
	char	*next;
	ssize_t	i;

	i = -1;
	*error = 1;
	next = NULL;
	if (*save != NULL)
	{
		if ((next = ft_strchr(*save, '\n')))
		{
			*next++ = '\0';
			*line = ft_strdup(*save);
			while (next[++i])
				(*save)[i] = next[i];
			(*save)[i] = '\0';
		}
		else
			*line = ft_strdup(*save);
	}
	else
		*line = ft_strdup("");
	if (*line == NULL)
		*error = -1;
	return (next);
}

char		*ft_checkbuff(char *next, char **save, char *buff, ssize_t *err)
{
	char	*tmp;

	if ((next = ft_strchr(buff, '\n')))
	{
		*next++ = '\0';
		tmp = *save;
		*save = ft_strdup(next);
		if (*save == NULL)
			*err = -1;
		ft_freeptr(&tmp);
	}
	return (next);
}

int		ft_readbuff(int fd, char **line, char **save, ssize_t *err)
{
	char			buff[BUFFER_SIZE + 1];
	char			*next;
	char			*tmp;

	next = ft_checksave(save, line, err);
	while (*err > 0 && !next && (*err = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[*err] = '\0';
		next = ft_checkbuff(next, save, buff, err);
		tmp = *line;
		if (*err < 0 || !(*line = ft_strjoin(*line, buff)))
		{
			ft_freeptr(save);
			ft_freeptr(&tmp);
			return (-1);
		}
		ft_freeptr(&tmp);
	}
	if (next == NULL || *err < 0)
	{
		ft_freeptr(save);
		*err < 0 ? ft_freeptr(line) : *err;
		return (*err < 0 ? -1 : 0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static	char	*save;
	char		*test;
	ssize_t		error;

	test = NULL;
	if (fd < 0 || !line || read(fd, test, 0))
		return (-1);
	return (ft_readbuff(fd, line, &save, &error));
}
