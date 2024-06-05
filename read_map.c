#include "so_long.h"

void	read_file(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);

	if (fd == -1)
	{
		return (NULL);
	}
	line = "1";
	while (line != NULL)
	{
		line = get_next_line(fd);
	}

}
