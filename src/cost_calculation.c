/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_calculation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:53:26 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/23 18:11:05 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	calculate_cost_ba(t_stack *a, t_stack *b, t_node *node, t_cost *c)
{
	int	costs[4];
	int	best_case;
	int	cost;
	int	rra_cost;
	int	rrb_cost;

	c->target_node = node;
	c->index_stack_b = get_node_index(b, node);
	c->index_stack_a = find_place_in_a(a, node->value);
	calculate_four_costs(a, b, c, costs);
	best_case = find_best_case(costs);
	cost = costs[best_case - 1];
	rra_cost = a->size - c->index_stack_a;
	rrb_cost = b->size - c->index_stack_b;
	if (best_case == 1)
		set_case_one_cost(c, c->index_stack_a, c->index_stack_b);
	else if (best_case == 2)
		set_case_two_cost(c, rra_cost, rrb_cost);
	else if (best_case == 3)
		set_case_three_cost(c, c->index_stack_a, rrb_cost, cost);
	else
		set_case_four_cost(c, rra_cost, c->index_stack_b, cost);
}

void	calculate_cost_ab(t_stack *a, t_stack *b, t_node *node, t_cost *c)
{
	int	costs[4];
	int	best_case;
	int	cost;
	int	rra_cost;
	int	rrb_cost;

	c->target_node = node;
	c->index_stack_a = get_node_index(a, node);
	c->index_stack_b = find_place_in_b(b, node->value);
	calculate_four_costs(a, b, c, costs);
	best_case = find_best_case(costs);
	cost = costs[best_case - 1];
	rra_cost = a->size - c->index_stack_a;
	rrb_cost = b->size - c->index_stack_b;
	if (best_case == 1)
		set_case_one_cost(c, c->index_stack_a, c->index_stack_b);
	else if (best_case == 2)
		set_case_two_cost(c, rra_cost, rrb_cost);
	else if (best_case == 3)
		set_case_three_cost(c, c->index_stack_a, rrb_cost, cost);
	else
		set_case_four_cost(c, rra_cost, c->index_stack_b, cost);
}

void	calculate_four_costs(t_stack *a, t_stack *b, t_cost *c, int costs[4])
{
	if (c->index_stack_a > c->index_stack_b)
		costs[0] = c->index_stack_a;
	else
		costs[0] = c->index_stack_b;
	if ((a->size - c->index_stack_a) > (b->size - c->index_stack_b))
		costs[1] = a->size - c->index_stack_a;
	else
		costs[1] = b->size - c->index_stack_b;
	costs[2] = c->index_stack_a + (b->size - c->index_stack_b);
	costs[3] = (a->size - c->index_stack_a) + c->index_stack_b;
}

int	find_best_case(int costs[4])
{
	int	min_cost;
	int	best_case;
	int	i;

	min_cost = costs[0];
	best_case = 1;
	i = 1;
	while (i < 4)
	{
		if (costs[i] < min_cost)
		{
			min_cost = costs[i];
			best_case = i + 1;
		}
		i++;
	}
	return (best_case);
}

int	get_node_index(t_stack *stack, t_node *target)
{
	int		index;
	t_node	*current;

	index = 0;
	current = stack->head;
	while (current && current != target)
	{
		index++;
		current = current->next;
	}
	return (index);
}
