/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:03:10 by magebreh          #+#    #+#             */
/*   Updated: 2025/05/30 21:40:30 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	sort_two(t_stack *a, t_stack *b)
{
	if (a->head->value > a->head->next->value)
		execute_instruction(a, b, "sa");
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

 void	sort_four_five(t_stack *a, t_stack *b)
{
	int		pushes;
	t_node	*current;
	int		min_val;
	int		pos;
	int		min_index;
	int		rotation;

	pushes = a->size - 3;
	while (pushes)
	{
		current = a->head;
		min_val = current->value;
		pos = 0;
		min_index = 0;
		while (current)
		{
			if (current->value < min_val)
			{
				min_val = current->value;
				min_index = pos;
			}
			current = current->next;
			pos++;
		}
		if (min_index <= pos / 2)
		{
			while (min_index)
			{
				execute_instruction(a, b, "ra");
				min_index--;
			}
			execute_instruction(a, b, "pb");
		}
		else 
		{
			rotation = pos-min_index;
			while (rotation)
			{
				execute_instruction(a, b, "rra");
				rotation--;
			}
			execute_instruction(a, b, "pb");
		}
		pushes--;
	}
	sort_three(a, b);
	while (b->size > 0)
		execute_instruction(a, b, "pa");
}


void	small_sort(t_stack *a, t_stack *b)
{
	if (a->size == 2)
		sort_two(a, b);
	else if (a->size == 3)
		sort_three(a, b);
	else
		sort_four_five(a, b);
}
