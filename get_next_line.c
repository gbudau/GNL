/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:15:15 by gbudau            #+#    #+#             */
/*   Updated: 2019/12/23 22:40:59 by gbudau           ###   ########.fr       */
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
	char	*tmp;
	size_t	len;

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
		{
			*line = ft_strdup(*rest);
			len = ft_strlen(*rest);
			tmp = *rest;
			while (len--)
				*tmp++ = '\0';
		}
	}
	else
		*line = ft_strdup("");
	return (next);
}

int			get_next_line(int fd, char **line)
{
	static	char	*rest;
	char			buffer[BUFFER_SIZE + 1];
	ssize_t			bytesread;
	char			*next;
	char			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, buffer, 0))
		return (-1);
	next = ft_checkrest(&rest, line);
	while (next == NULL && (bytesread = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[bytesread] = '\0';
		if ((next = ft_strchr(buffer, '\n')))
		{
			*next++ = '\0';
			tmp = rest;
			rest = ft_strdup(next);
			free(tmp);
		}
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buffer)) || bytesread < 0)
		{
			ft_freeptr(&tmp);
			return (-1);
		}
		ft_freeptr(&tmp);
	}
	if (next == NULL)
	{
		ft_freeptr(&rest);
		return (0);
	}
	return (ft_strlen(*line) || rest ? 1 : 0);
}
