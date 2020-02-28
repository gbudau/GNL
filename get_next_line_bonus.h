/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:15:26 by gbudau            #+#    #+#             */
/*   Updated: 2020/02/28 13:12:03 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct	s_gnl
{
		int fd;
		char *save;
		struct s_gnl *next;
} 		t_gnl;

size_t		gnl_strlen(const char *s);
char		*gnl_strcpy(char *dst, const char *src);
char		*gnl_strdup(const char *s1);
char		*gnl_strchr(const char *s, int c);
char		*gnl_strjoinfree(char *s1, char const *s2);
int		get_next_line(int fd, char **line);

#endif
