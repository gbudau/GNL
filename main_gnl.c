#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../libft/libft.h"

int	main(int argc, char **argv)
{
	char	*line;
	int	fd;
	int	ln;

	if (argc == 3)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			printf("Open error\n");
			return (0);
		}
		if ((ln = ft_atoi(argv[2])) <= 0)
		{
			printf("Enter the number of lines you want to read from the file\n");
			return (0);
		}
		else
		{
			while (get_next_line(fd, &line) && ln--)
			{
				printf("%s\n", line);
				free(line);
				line = NULL;
			}
			free(line);
			line = NULL;
		}
		if (close(fd) < 0)
			printf("Close error\n");
	}
	else
		printf("Usage is ./executable file lines\n");
	return (0);
}
