/*
 * Лабораторная работа №4
 * Студент: номер 10
 * Вариант: 2 (Фильтрация строк по критериям)
 */

#include "libft.h"
#include <stdarg.h>

int	predicate_len(const char *str, ...)
{
	va_list	args;
	int		threshold;

	va_start(args, str);
	threshold = va_arg(args, int);
	va_end(args);
	return ((int)ft_strlen(str) > threshold);
}

int	predicate_start(const char *str, ...)
{
	va_list	args;
	char	*prefix;

	va_start(args, str);
	prefix = va_arg(args, char *);
	va_end(args);
	return (ft_strncmp(str, prefix, ft_strlen(prefix)) == 0);
}

int	predicate_digit(const char *str, ...)
{
	int	i;

	(void)str;
	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

typedef struct s_filter
{
	char	*name;
	int		(*predicate)(const char *str, ...);
}	t_filter;

t_filter	filters[] = {
	{"len", predicate_len},
	{"start", predicate_start},
	{"digit", predicate_digit},
	{NULL, NULL}
};

int	get_filter_index(const char *name)
{
	int	i;

	i = 0;
	while (filters[i].name)
	{
		if (ft_strncmp(filters[i].name, name, ft_strlen(name) + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**read_lines_from_stdin(int *count)
{
	char	buffer[4096];
	char	*all;
	char	**lines;
	int		bytes_read;

	all = ft_strdup("");
	if (!all)
		return (NULL);
	bytes_read = read(0, buffer, 4095);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		all = ft_strjoin(all, buffer);
		if (!all)
			return (NULL);
		bytes_read = read(0, buffer, 4095);
	}
	lines = ft_split(all, '\n');
	free(all);
	*count = 0;
	if (lines)
	{
		while (lines[*count])
			(*count)++;
	}
	return (lines);
}

int	main(int argc, char **argv)
{
	int		filter_idx;
	int		i;
	int		threshold;
	char	**strings;
	int		string_count;

	if (argc < 3)
	{
		ft_putstr_fd("Error: insufficient arguments\n", 2);
		return (1);
	}
	filter_idx = get_filter_index(argv[1]);
	if (filter_idx == -1)
	{
		ft_putstr_fd("Error: unknown filter\n", 2);
		return (1);
	}
	if (filter_idx == 0 && argc < 4)
	{
		ft_putstr_fd("Error: len filter requires threshold\n", 2);
		return (1);
	}
	if (filter_idx == 1 && argc < 4)
	{
		ft_putstr_fd("Error: start filter requires prefix\n", 2);
		return (1);
	}
	if (filter_idx == 0)
	{
		threshold = ft_atoi(argv[2]);
		strings = argv + 3;
		string_count = argc - 3;
	}
	else if (filter_idx == 1)
	{
		strings = argv + 3;
		string_count = argc - 3;
	}
	else
	{
		strings = argv + 2;
		string_count = argc - 2;
	}
	if (string_count == 0)
	{
		strings = read_lines_from_stdin(&string_count);
		if (!strings)
			return (1);
	}
	i = 0;
	while (i < string_count)
	{
		int	match = 0;
		if (filter_idx == 0)
			match = predicate_len(strings[i], threshold);
		else if (filter_idx == 1)
			match = predicate_start(strings[i], argv[2]);
		else
			match = predicate_digit(strings[i]);
		if (match)
			ft_putendl_fd(strings[i], 1);
		i++;
	}
	if (string_count > 0 && (argc < 4 || filter_idx == 2))
	{
		i = 0;
		while (strings[i])
			free(strings[i++]);
		free(strings);
	}
	return (0);
}
