/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:15:15 by gbudau            #+#    #+#             */
/*   Updated: 2019/12/24 00:28:42 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"


static char	*ft_checkrest(char **rest, char **line, char *next)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (*rest != 0)
	{
		tmp = *rest;
		if ((next = ft_strchr(*rest, '\n')))
		{
			*next++ = '\0';
			*line = ft_strdup(*rest);
			tmp[i] = next[i];
			while (next[++i])
				tmp[i] = next[i];
			tmp[i] = '\0';
		}
		else
			*line = ft_strdup(*rest);
	}
	else
		*line = ft_strdup("");
	return (next);
}

static char		*ft_checkbuff(char *next, char **rest, char *buff)
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

static int			ft_readbuff(int fd, char **line, char **rest, char *next)
{
	char			buff[BUFFER_SIZE + 1];
	ssize_t			br;
	char			*tmp;

	tmp = NULL;
	while (next == NULL && (br = read(fd, buff, BUFFER_SIZE)))
	{
		buff[br] = '\0';
		next = ft_checkbuff(next, rest, &buff[0]);
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

static t_gnl		*ft_lstnewfd(int fd)
{
	t_gnl	*new;

	new = malloc(sizeof(t_gnl));
	if (new == NULL)
		return (NULL);
	new->rest = NULL;
	new->fd = fd;
	new->next = NULL;
	return (new);
}

int			get_next_line(int fd, char **line)
{
	static t_gnl		*head;
	t_gnl			*tmp;
	char			*next;
	int			ret;

	next = NULL;
	if (fd < 0 || !line || read(fd, next, 0))
		return (-1);
	(head == NULL) ? head = ft_lstnewfd(fd) : head;
	if (head == NULL)
		return (-1);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = ft_lstnewfd(fd);
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (-1);
	next = ft_checkrest(&tmp->rest, line, next);
	ret = ft_readbuff(tmp->fd, line, &tmp->rest, next);
	if (ret <= 0)
		ft_lstfreenode(tmp->fd, &head);
	return (ret);
}
