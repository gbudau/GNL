#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (dst == src)
		return (dst);
	while (n--)
		*d++ = *s++;
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char			*str;

	str = b;
	while (len--)
		*str++ = (unsigned char)c;
	return (b);
}

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s1);
	if (!(ret = malloc(len + 1)))
		return (NULL);
	ft_memcpy(ret, s1, len + 1);
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len;
	size_t	s1len;
	size_t	s2len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (ft_strdup(s1));
	else if (s1 == NULL)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	len = s1len + s2len + 1;
	if (!(ret = malloc(len)))
		return (NULL);
	ft_memcpy(ret, s1, s1len);
	ft_memcpy(ret + s1len, s2, s2len + 1);
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	const char		*p;

	p = s;
	while (*p)
	{
		if (*p == (const char)c)
			return ((char *)p);
		p++;
	}
	if (*p == (const char)c)
		return ((char *)p);
	return (NULL);
}

char	*ft_strnew(size_t size)
{
	char	*ret;

	if (!(ret = malloc(size + 1)))
		return (NULL);
	ft_memset(ret, 0, size + 1);
	return (ret);
}

void	ft_freeptr(char **ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	*ptr = NULL;
}

char	*ft_checkrest(char **rest, char **line)
{
	char *next;

	next = NULL;
	if (*rest != 0)
	{
		if ((next = ft_strchr(*rest, '\n')))
		{
			*next = '\0';
			*line = ft_strdup(*rest);
			next++;
			ft_memcpy(*rest, next, ft_strlen(next) + 1);
		}
		else
		{
			*line = ft_strdup(*rest);
			ft_memset(*rest, 0, ft_strlen(*rest));
		}
	}
	else
	{
		*line = ft_strnew(0);
	}
	return (next);
}
	
int 	get_next_line(int fd, char **line)
{
	static	char 	*rest;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytesread;
	char		*next;
	char		*tmp;

	if (fd < 0 || fd > OPEN_MAX || line == NULL || BUFFER_SIZE <= 0 || read(fd, buffer, 0))
		return (-1);
	next = ft_checkrest(&rest, line);
	bytesread = 0;
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
