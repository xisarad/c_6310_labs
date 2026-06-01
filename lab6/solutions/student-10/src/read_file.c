#include "txtfile.h"
#include <fcntl.h>
#include <unistd.h>

static char	*get_next_line(int fd)
{
	char	*buffer;
	char	c;
	int		i;
	int		bytes;

	buffer = (char *)malloc(1024);
	if (!buffer)
		return (NULL);
	i = 0;
	bytes = read(fd, &c, 1);
	while (bytes > 0 && c != '\n')
	{
		buffer[i++] = c;
		bytes = read(fd, &c, 1);
	}
	if (bytes <= 0 && i == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	return (buffer);
}

char	**read_file(const char *filename)
{
	int		fd;
	char	**lines;
	char	*line;
	int		count;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines = (char **)realloc(lines, (count + 2) * sizeof(char *));
		if (!lines)
		{
			free(line);
			close(fd);
			return (NULL);
		}
		lines[count] = line;
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	if (lines)
		lines[count] = NULL;
	return (lines);
}
