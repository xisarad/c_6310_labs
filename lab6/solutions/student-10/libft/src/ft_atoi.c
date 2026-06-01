#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	result;
	long	check;

	sign = 1;
	result = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		check = result;
		result = result * 10 + (*nptr - '0');
		// Проверка переполнения: если новое значение меньше предыдущего — переполнение
		if (result < check && sign == 1)
			return (2147483647);
		if (result < check && sign == -1)
			return (-2147483648);
		nptr++;
	}
	return ((int)(sign * result));
}