/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mechanical_turk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:48:07 by magebreh          #+#    #+#             */
/*   Updated: 2025/05/31 18:48:39 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void calculate_cost(t_stack *a, t_stack *b, t_node *node, t_cost *cost)
{
	t_node *current;
	int pos;

	current = a->head;
	pos = 0;
	while (current)
	{
		if(current== node)
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
}

void find_insert_pos_b(t_stack *b, t_node *node, t_cost *cost)
{
	t_node *current;
	int min_index;
	int max_index;
	int	pos;

	current = b->head;
	pos = 0;
	while (current)
	{
		if(current->value > node->value && current->next->value < node->value)
		{
			cost->index_Stack_b = pos;
			break;
		}
		current = current->next;
		pos++;
	}
	cost->index_Stack_b = 0;
}

void	mechanical_turk(t_stack *a, t_stack *b)
{

}