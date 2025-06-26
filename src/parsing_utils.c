/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:31:32 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/26 14:35:58 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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

void	free_split_arg(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

bool	stack_append(t_stack *stack_a, int val)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (false);
	node->value = val;
	node->next = NULL;
	node->prev = NULL;
	if (stack_a->head == NULL)
	{
		stack_a->head = node;
		stack_a->tail = node;
	}
	else
	{
		node->prev = stack_a->tail;
		stack_a->tail->next = node;
		stack_a->tail = node;
	}
	stack_a->size++;
	return (true);
}

void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	current = stack-> head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	stack->head = NULL;
	stack->tail = NULL;
	stack->size = 0;
}
