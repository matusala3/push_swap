/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mechanical_turk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:48:07 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/09 14:43:41 by magebreh         ###   ########.fr       */
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
		current = current->next;
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

	printf("=== DEBUG find_insert_pos_b ===\n");
    printf("Looking for position of node->value = %d\n", node->value);
	current = b->head;
	pos = 0;
	min_value = current->value;
	printf("Starting: min_value = %d\n", min_value);
	while (current && current->next)
	{
		if(current->value > node->value && current->next->value < node->value)
		{
			printf("FOUND INSERT SPOT: between %d and %d at position %d\n", 
                   current->value, current->next->value, pos + 1);
			cost->index_stack_b = pos + 1;
			return true;
		}
		if(current->next->value < min_value)
		{
			min_value = current->next->value;	
			cost->index_stack_b = pos + 1;
			printf("New minimum found: %d at position %d\n", min_value, pos + 1);
		}
		current = current->next;
		pos++;
	}
	return false;
}

bool find_insert_pos_a(t_stack *a, t_node *node, t_cost *cost)
{
	t_node *current;
	int min_value;
	int min_index;
	int	pos;

	current = a->head;
	pos = 0;
	min_value = current->value;
	min_index = 0;
	while (current && current->next)
	{
		if(current->value < node->value && current->next->value > node->value)
		{
			cost->index_stack_a = pos + 1;
			return true;
		}
		if(current->next->value < min_value)
		{
			min_value = current->next->value;
			min_index = pos + 1;
		}
		current = current->next;
		pos++;
	}
	cost->index_stack_a = min_index;
	return false;
}

void perform_optimal_move(t_stack *a, t_stack *b, t_cost *best) 
{
	bool both_forward = (ft_strcmp(best->dir_a, "ra") == 0 && ft_strcmp(best->dir_b, "rb") == 0); 
	bool both_reverse = (ft_strcmp(best->dir_a, "rra") == 0 && ft_strcmp(best->dir_b, "rrb") == 0);

    while (best->cost_top_a > 0 && best->cost_top_b > 0 && 
           (both_forward || both_reverse)) 
    {
        if(ft_strcmp(best->dir_a, "ra") == 0) 
            execute_instruction(a, b, "rr");
        else 
            execute_instruction(a, b, "rrr");
        best->cost_top_a--;
        best->cost_top_b--;
    }
    while (best->cost_top_a-- > 0)
        execute_instruction(a, b, best->dir_a);
    while (best->cost_top_b-- > 0)
        execute_instruction(a, b, best->dir_b);
    execute_instruction(a, b, "pb");
}

void push_back_b_to_a(t_stack *a, t_stack *b)
{
	t_cost cost;

	while (b->size > 0)
	{
		find_insert_pos_a(a, b->head, &cost);
		if (cost.index_stack_a <= a->size / 2)
		{
			int i = cost.index_stack_a;
			while (i-- > 0)
				execute_instruction(a, b, "ra");
		}
		else
		{
			int i = a->size - cost.index_stack_a;
			while (i-- > 0)
				execute_instruction(a, b, "rra");
		}

		execute_instruction(a, b, "pa");
	}
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
