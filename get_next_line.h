/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:15:26 by gbudau            #+#    #+#             */
/*   Updated: 2020/04/03 16:18:13 by gbudau           ###   ########.fr       */
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

size_t	gnl_strlen(const char *s);
char	*gnl_strcpy(char *dst, const char *src);
char	*gnl_strdup(const char *s1);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin_free(char *s1, char const *s2);
int		get_next_line(int fd, char **line);

#endif
