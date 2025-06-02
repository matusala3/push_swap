/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mechanical_turk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:48:07 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/02 23:37:49 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include <stdbool.h>

void calculate_cost(t_stack *a, t_stack *b, t_node *node, t_cost *cost)
{
	t_node *current;
	int pos;

	current = a->head;
	pos = 0;
	while (current)
	{
		if(current == node)
		{
			cost->index_stack_a = pos;
			break;
		}
		pos++;
	}
	if(cost->index_stack_a <= a->size / 2)
	{
		cost->cost_top_a = cost->index_stack_a;
		cost->dir_a = "ra";
	}
	else
	{
		cost->cost_top_a = a->size - cost->index_stack_a;
		cost->dir_a = "rra";
	}
	if (cost->index_stack_b <= b->size / 2)
	{
		cost->cost_top_b = cost->index_stack_b;
		cost->dir_b = "rb";
	}
	else
	{
		cost->cost_top_b = b->size - cost->index_stack_b;
		cost->dir_b = "rrb";
	}
	if (ft_strcmp(cost->dir_a, cost->dir_b) == 0)
	{
		if (cost->cost_top_a > cost->cost_top_b)
			cost->total_cost = cost->cost_top_a;
		else
			cost->total_cost = cost->cost_top_b;
	}
	else
		cost->total_cost = cost->cost_top_a + cost->cost_top_b;
}

bool find_insert_pos_b(t_stack *b, t_node *node, t_cost *cost)
{
	t_node *current;
	int min_value;
	int	pos;

	current = b->head;
	pos = 0;
	min_value = current->value;
	while (current && current->next)
	{
		if(current->value > node->value && current->next->value < node->value)
		{
			cost->index_stack_b = pos + 1;
			return true;
		}
		if(current->next->value < min_value)
		{
			min_value = current->next->value;
			cost->index_stack_b = pos + 1;
		}
		current = current->next;
		pos++;
	}
	return false;
}

void mechanical_turk(t_stack *a, t_stack *b)
{
	t_cost best_cost;
	t_cost current_cost;
	t_node *current;
	t_node *best_node;

	execute_instruction(a, b, "pb");
	execute_instruction(a, b, "pb");

	while (a->size > 3)
	{
		current = a->head;
		best_cost.total_cost = INT_MAX;
		best_node = NULL;

		while (current)
		{
			if (!find_insert_pos_b(b, current, &current_cost))
			{
				if (current->value > b->head->value)
					current_cost.index_stack_b = 0;
			}
			calculate_cost(a, b, current, &current_cost);
			if (current_cost.total_cost < best_cost.total_cost)
			{
				best_cost = current_cost;
				best_node = current;
			}
			current = current->next;
		}
		perform_optimal_move(a, b, &best_cost);
	}
	sort_three(a, b);
	push_back_b_to_a(a, b);
}
