#include "txtfile.h"
#include <fcntl.h>
#include <unistd.h>

static int	count_lines_and_max_len(const char *filename, int *max_len)
{
	int		fd;
	char	buf[1];
	int		bytes;
	int		lines;
	int		current_len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 1;
	current_len = 0;
	*max_len = 0;
	bytes = read(fd, buf, 1);
	while (bytes > 0)
	{
		if (buf[0] == '\n')
		{
			lines++;
			if (current_len > *max_len)
				*max_len = current_len;
			current_len = 0;
		}
		else
			current_len++;
		bytes = read(fd, buf, 1);
	}
	close(fd);
	if (current_len > *max_len)
		*max_len = current_len;
	return (lines);
}

static char	*read_line(int fd, int max_len)
{
	char	*buffer;
	char	c;
	int		i;
	int		bytes;

	buffer = (char *)malloc(max_len + 2);
	if (!buffer)
		return (NULL);
	i = 0;
	bytes = read(fd, &c, 1);
	while (bytes > 0 && c != '\n')
	{
		buffer[i++] = c;
		bytes = read(fd, &c, 1);
	}
	buffer[i] = '\0';
	return (buffer);
}

char	**read_file(const char *filename)
{
	int		fd;
	char	**lines;
	int		total_lines;
	int		max_len;
	int		i;

	total_lines = count_lines_and_max_len(filename, &max_len);
	if (total_lines <= 0)
		return (NULL);
	lines = (char **)malloc((total_lines + 1) * sizeof(char *));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(lines);
		return (NULL);
	}
	i = 0;
	while (i < total_lines)
	{
		lines[i] = read_line(fd, max_len);
		if (!lines[i])
		{
			while (--i >= 0)
				free(lines[i]);
			free(lines);
			close(fd);
			return (NULL);
		}
		i++;
	}
	lines[total_lines] = NULL;
	close(fd);
	return (lines);
}
