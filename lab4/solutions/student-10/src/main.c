/*
 * Лабораторная работа №4
 * Студент: номер 10
 * Вариант: 2 (Фильтрация строк по критериям)
 */

#include "libft.h"
#include <stdarg.h>

int	match(const char *str, int criterion, ...)
{
	va_list	args;
	int		result;

	va_start(args, criterion);
	result = 0;
	if (criterion == 0)
	{
		int	threshold = va_arg(args, int);
		result = ((int)ft_strlen(str) > threshold);
	}
	else if (criterion == 1)
	{
		char	*prefix = va_arg(args, char *);
		result = (ft_strncmp(str, prefix, ft_strlen(prefix)) == 0);
	}
	else if (criterion == 2)
	{
		int	i = 0;
		result = 1;
		if (!str || str[0] == '\0')
			result = 0;
		else
		{
			while (str[i])
			{
				if (!ft_isdigit(str[i]))
				{
					result = 0;
					break;
				}
				i++;
			}
		}
	}
	va_end(args);
	return (result);
}

int	predicate_len(const char *str, ...)
{
	va_list	args;
	int		threshold;

	va_start(args, str);
	threshold = va_arg(args, int);
	va_end(args);
	return (match(str, 0, threshold));
}

int	predicate_start(const char *str, ...)
{
	va_list	args;
	char	*prefix;

	va_start(args, str);
	prefix = va_arg(args, char *);
	va_end(args);
	return (match(str, 1, prefix));
}

int	predicate_digit(const char *str, ...)
{
	(void)str;
	return (match(str, 2));
}

static int	get_filter_index(const char *name)
{
	static struct s_filter
	{
		char	*name;
		int		(*predicate)(const char *str, ...);
	}	filters[] = {
		{"len", predicate_len},
		{"start", predicate_start},
		{"digit", predicate_digit},
		{NULL, NULL}
	};
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

static char	**read_lines_from_stdin(int *count)
{
	char	buffer[4096];
	char	*all;
	char	*temp;
	char	**lines;
	int		bytes_read;

	all = ft_strdup("");
	if (!all)
		return (NULL);
	bytes_read = read(0, buffer, 4095);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(all, buffer);
		free(all);
		if (!temp)
			return (NULL);
		all = temp;
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
		int	match_result = 0;
		if (filter_idx == 0)
			match_result = predicate_len(strings[i], threshold);
		else if (filter_idx == 1)
			match_result = predicate_start(strings[i], argv[2]);
		else
			match_result = predicate_digit(strings[i]);
		if (match_result)
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