#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	result;
	long	check;

	sign = 1;
	result = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\v' || *nptr == '\f' || *nptr == '\r')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		check = result;
		result = result * 10 + (*nptr - '0');
		if (result < check && sign == 1)
			return (2147483647);
		if (result < check && sign == -1)
			return (-2147483648);
		nptr++;
	}
	return ((int)(sign * result));
}
