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

static void	checksave(char **save, char **line, char **next, ssize_t *ret)
{
	ssize_t	i;

	i = -1;
	*ret = 0;
	if (*save != NULL)
	{
		if ((*next = ft_strchr(*save, '\n')))
		{
			*ret = 1;
			*(*next)++ = '\0';
			*line = ft_strdup(*save);
			while ((*next)[++i])
				(*save)[i] = (*next)[i];
			(*save)[i] = '\0';
		}
		else
			*line = ft_strdup(*save);
	}
	else
		*line = ft_strdup("");
	if (*line == NULL)
		*ret = -1;
}

static void	checkbuff(char **next, char **save, char *buff, ssize_t *ret)
{
	char	*tmp;

	if ((*next = ft_strchr(buff, '\n')))
	{
		*(*next)++ = '\0';
		tmp = *save;
		*save = ft_strdup(*next);
		if (*save == NULL)
			*ret = -1;
		ft_freeptr(&tmp);
	}
}

static void	readbuff(int fd, char **line, char **save, ssize_t *ret)
{
	char	buff[BUFFER_SIZE + 1];
	char	*next;
	char	*tmp;

	next = NULL;
	checksave(save, line, &next, ret);
	while (*ret >= 0 && !next && (*ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[*ret] = '\0';
		checkbuff(&next, save, buff, ret);
		tmp = *line;
		if (*ret > 0 && !(*line = ft_strjoin(*line, buff)))
		{
			ft_freeptr(&tmp);
			*ret = -1;
		}
		if (*ret < 0)
			break;
		ft_freeptr(&tmp);
	}
	if (next == NULL || *ret < 0)
		ft_freeptr(save);
	if (*ret < 0)
		ft_freeptr(line);
}

static t_gnl		*create_fd_list(int fd)
{
	t_gnl	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->save = NULL;
	new->fd = fd;
	new->next = NULL;
	return (new);
}

int			get_next_line(int fd, char **line)
{
	static t_gnl		*head;
	t_gnl			*tmp;
	char			*test;
	ssize_t			ret;

	test = NULL;
	if (fd < 0 || !line || read(fd, test, 0))
		return (-1);
	if (!head)
		if ((head = create_fd_list(fd)) == NULL)
			return (-1);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = create_fd_list(fd);
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (-1);
	readbuff(tmp->fd, line, &tmp->save, &ret);
	if (ret <= 0)
		ft_lstfreenode(tmp->fd, &head);
	return (ret > 1 ? 1 : ret);
}
