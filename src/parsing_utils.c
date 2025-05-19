#include "../include/parsing_utils.h"

bool safe_atoi(const char *str, int *out)
{
	int	i = 0;
	int	sign = 1;
	int	result = 0;

	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return false;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (INT_MAX - (str[i] - '0')) / 10)
			return false;
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return false;
	*out = result * sign;
	return true;
}

