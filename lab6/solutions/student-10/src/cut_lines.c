#include "txtfile.h"

static int	count_lines_array(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}

char	**cut_lines(char **lines, int start, int end)
{
	char	**result;
	int		total_lines;
	int		i;
	int		j;

	if (!lines || start <= 0 || end < start)
		return (NULL);
	total_lines = count_lines_array(lines);
	if (start > total_lines)
		return (NULL);
	if (end > total_lines)
		end = total_lines;
	result = (char **)malloc((end - start + 2) * sizeof(char *));
	if (!result)
		return (NULL);
	i = start - 1;
	j = 0;
	while (i <= end - 1)
	{
		result[j] = ft_strdup(lines[i]);
		if (!result[j])
		{
			while (--j >= 0)
				free(result[j]);
			free(result);
			return (NULL);
		}
		j++;
		i++;
	}
	result[j] = NULL;
	return (result);
}
