/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:15:15 by gbudau            #+#    #+#             */
/*   Updated: 2020/04/03 16:15:51 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static int		readbuff(int fd, char **line, char **save)
{
	char	buff[BUFFER_SIZE + 1];
	char	*next;
	ssize_t	error;

	error = checksave(save, line, &next);
	while (error > 0 && !next && (error = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[error] = '\0';
		if ((next = gnl_strchr(buff, '\n')))
		{
			*next++ = '\0';
			*save = gnl_strdup(next);
		}
		if ((next && !*save) || !(*line = gnl_strjoinfree(*line, buff)))
			error = -1;
	}
	if (!next || error < 0)
		if (*save)
			free(*save);
	if (error < 0)
		return (-1);
	return (next ? 1 : 0);
}

static t_gnl	*create_fd_list(int fd)
{
	t_gnl	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->save = NULL;
	new->fd = fd;
	new->next = NULL;
	return (new);
}

static void		gnl_lstfreenode(int fd, t_gnl **head)
{
	t_gnl	*del;
	t_gnl	**p;

	p = head;
	while (*p && (*p)->fd != fd)
		p = &(*p)->next;
	if (*p)
	{
		del = *p;
		*p = del->next;
		free(del);
	}
}

int				get_next_line(int fd, char **line)
{
	static t_gnl	*head;
	t_gnl			*tmp;
	char			*test;
	ssize_t			ret;

	test = NULL;
	if (fd < 0 || !line || read(fd, test, 0))
		return (-1);
	head = !head ? create_fd_list(fd) : head;
	tmp = head;
	while (tmp && tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = create_fd_list(fd);
		tmp = tmp->next;
	}
	if (!tmp)
		return (-1);
	ret = readbuff(tmp->fd, line, &tmp->save);
	if (ret <= 0)
		gnl_lstfreenode(tmp->fd, &head);
	return (ret);
}
