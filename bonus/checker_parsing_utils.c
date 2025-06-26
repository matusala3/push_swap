/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_parsing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:40:59 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/26 19:52:26 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/checker_bonus.h"

bool	parse_integer_safe(const char *str, int start_pos, int sign, int *out)
{
	long long	result;
	int			i;

	result = 0;
	i = start_pos;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (sign == 1 && result > 2147483647)
			return (false);
		if (sign == -1 && result > 2147483648LL)
			return (false);
		i++;
	}
	if (str[i] != '\0')
		return (false);
	*out = (int)(result * sign);
	return (true);
}

bool	safe_atoi(const char *str, int *out)
{
	int	i;
	int	sign;

	if (!str || !out)
		return (false);
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (false);
	return (parse_integer_safe(str, i, sign, out));
}

void	trim_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
