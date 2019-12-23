#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif
#include <stdlib.h>
#include <unistd.h>

int 	get_next_line(int fd, char **line);

#endif
