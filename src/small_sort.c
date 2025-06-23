/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:03:10 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/23 14:26:30 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	sort_two(t_stack *a, t_stack *b, char stack)
{
	if (stack == 'a' && a->head->value > a->head->next->value)
		execute_instruction(a, b, "sa");
	else if (stack == 'b' && b->head->value < b->head->next->value)
		execute_instruction(a, b, "sb");
}

void	sort_three(t_stack *a, t_stack *b)
{
	int	x;
	int	y;
	int	z;

	x = a->head->value;
	y = a->head->next->value;
	z = a->tail->value;
	if (x < y && y < z)
		return ;
	else if (x > y && y < z && x < z)
		execute_instruction(a, b, "sa");
	else if (x > y && y > z)
	{
		execute_instruction(a, b, "sa");
		execute_instruction(a, b, "rra");
	}
	else if (x > y && y < z && x > z)
		execute_instruction(a, b, "ra");
	else if (x < y && y > z && x < z)
	{
		execute_instruction(a, b, "sa");
		execute_instruction(a, b, "ra");
	}
	else if (x < y && y > z && x > z)
		execute_instruction(a, b, "rra");
}

void	find_min(t_stack *a, int *min_val, int *min_index)
{
	t_node	*current;
	int		pos;

	current = a->head;
	*min_val = current->value;
	pos = 0;
	*min_index = 0;
	while (current)
	{
		if (current->value < *min_val)
		{
			*min_val = current->value;
			*min_index = pos;
		}
		current = current->next;
		pos++;
	}
}

void	sort_four_five(t_stack *a, t_stack *b)
{
	int	pushes;
	int	min_val;
	int	min_index;
	int	rotation;

	pushes = a->size - 3;
	while (pushes--)
	{
		find_min(a, &min_val, &min_index);
		if (min_index <= a->size / 2)
			while (min_index--)
				execute_instruction(a, b, "ra");
		else
		{
			rotation = a->size - min_index;
			while (rotation--)
				execute_instruction(a, b, "rra");
		}
		execute_instruction(a, b, "pb");
	}
	sort_three(a, b);
	while (b->size > 0)
		execute_instruction(a, b, "pa");
}

void	small_sort(t_stack *a, t_stack *b)
{
	if (a->size == 2)
		sort_two(a, b, 'a');
	else if (a->size == 3)
		sort_three(a, b);
	else
		sort_four_five(a, b);
}
