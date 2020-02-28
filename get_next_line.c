/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:15:15 by gbudau            #+#    #+#             */
/*   Updated: 2020/02/28 12:42:43 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	checksave(char **save, char **line, char **next)
{
	if (*save == NULL)
	{
		*line = gnl_strdup("");
		*next = NULL;
		return (*line ? 1 : -1);
	}
	if ((*next = gnl_strchr(*save, '\n')))
	{
		*(*next)++ = '\0';
		*line = gnl_strdup(*save);
		gnl_strcpy(*save, *next);
	}
	else
	{
		*line = gnl_strdup(*save);
		free(*save);
		*save = NULL;
	}
	return (*line ? 1 : -1);
}

int		get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	char			*next;
	ssize_t			error;
	static	char		*save;

	if (fd < 0 || !line || read(fd, save, 0))
		return (-1);
	error = checksave(&save, line, &next);
	while (error > 0 && !next && (error = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[error] = '\0';
		if ((next = gnl_strchr(buff, '\n')))
		{
			*next++ = '\0';
			save = gnl_strdup(next);
		}
		if ((next && !save) || !(*line = gnl_strjoin_free(*line, buff)))
			error = -1;
	}
	if (next == NULL || error < 0)
		if (save)
			free(save);
	if (error < 0)
		return (-1);
	return (next ? 1 : 0);
}
