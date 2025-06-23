/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:40:14 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/23 18:29:14 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_node	*get_node_at(t_stack *stack, int index)
{
	t_node	*current;
	int		i;

	current = stack->head;
	i = 0;
	while (current && i < index)
	{
		current = current->next;
		i++;
	}
	return (current);
}

int	find_place_in_b(t_stack *b, int value)
{
	int		max_i;
	int		min_i;
	t_node	*max_node;
	t_node	*min_node;

	max_i = get_index_of_max(b);
	min_i = get_index_of_min(b);
	max_node = get_node_at(b, max_i);
	min_node = get_node_at(b, min_i);
	if (max_node && value > max_node->value)
		return (max_i);
	if (min_node && value < min_node->value)
		return (min_i + 1);
	return (get_index_between(b, value, 'b'));
}

int	get_index_of_min(t_stack *b)
{
	int		min;
	int		index;
	int		i;
	t_node	*current;

	min = b->head->value;
	index = 0;
	i = 1;
	current = b->head->next;
	while (current)
	{
		if (current->value < min)
		{
			min = current->value;
			index = i;
		}
		current = current->next;
		i++;
	}
	return (index);
}

int	get_index_of_max(t_stack *s)
{
	int		max;
	int		index;
	int		i;
	t_node	*current;

	max = s->head->value;
	index = 0;
	i = 0;
	current = s->head;
	while (current)
	{
		if (current->value > max)
		{
			max = current->value;
			index = i;
		}
		current = current->next;
		i++;
	}
	return (index);
}

int	find_place_in_a(t_stack *a, int value)
{
	int		max_i;
	int		min_i;
	t_node	*max_node;
	t_node	*min_node;

	max_i = get_index_of_max(a);
	min_i = get_index_of_min(a);
	max_node = get_node_at(a, max_i);
	min_node = get_node_at(a, min_i);
	if (value < min_node->value)
		return (min_i);
	if (value > max_node->value)
		return (max_i + 1);
	return (get_index_between(a, value, 'a'));
}
