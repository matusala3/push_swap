/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mechanical_turk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:48:07 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/23 18:27:11 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"


void	set_case_one_cost(t_cost *c, int a_cost, int b_cost)
{
	c->cost_top_a = a_cost;
	c->cost_top_b = b_cost;
	c->dir_a = "ra";
	c->dir_b = "rb";
	if (a_cost > b_cost)
		c->total_cost = a_cost;
	else
		c->total_cost = b_cost;
	c->case_id = 1;
}

void	set_case_two_cost(t_cost *c, int rra_cost, int rrb_cost)
{
	c->cost_top_a = rra_cost;
	c->cost_top_b = rrb_cost;
	c->dir_a = "rra";
	c->dir_b = "rrb";
	if (rra_cost > rrb_cost)
		c->total_cost = rra_cost;
	else
		c->total_cost = rrb_cost;
	c->case_id = 2;
}

void	set_case_three_cost(t_cost *c, int ra_cost, int rrb_cost, int total)
{
	c->cost_top_a = ra_cost;
	c->cost_top_b = rrb_cost;
	c->dir_a = "ra";
	c->dir_b = "rrb";
	c->total_cost = total;
	c->case_id = 3;
}

void	set_case_four_cost(t_cost *c, int rra_cost, int rb_cost, int total)
{
	c->cost_top_a = rra_cost;
	c->cost_top_b = rb_cost;
	c->dir_a = "rra";
	c->dir_b = "rb";
	c->total_cost = total;
	c->case_id = 4;
}

int get_index_between(t_stack *stack, int value, char direction)
{
    t_node *current;
    int index;

    current = stack->head;
    index = 0;

    while (current && current->next)
    {
        if (direction == 'b')
        {
            if (current->value > value && current->next->value < value)
                return index + 1;
        }
        else if (direction == 'a')
        {
            if (current->value < value && current->next->value > value)
                return index + 1;
        }
        current = current->next;
        index++;
    }
    return 0;
}

void seed_stack_b(t_stack *a, t_stack *b)
{
	execute_instruction(a, b, "pb");
	execute_instruction(a, b, "pb");
    
    sort_two(a, b, 'b');
}


void final_align_a(t_stack *a)
{
    int min_index;
    int i;

    min_index = get_index_of_min(a);

    if (min_index <= a->size / 2)
    {
        while (min_index-- > 0)
            execute_instruction(a, NULL, "ra");
    }
    else
    {
        i = 0;
        while (i < a->size - min_index)
        {
            execute_instruction(a, NULL, "rra");
            i++;
        }
    }
}

void push_cheapest_to_b(t_stack *a, t_stack *b)
{
    t_cost cheapest;
    t_node *current;
    t_cost current_cost;
    
    current = a->head;
    cheapest.total_cost = INT_MAX;

    while (current)
    {
        calculate_cost_ab(a, b, current, &current_cost);
        if (current_cost.total_cost < cheapest.total_cost)
            cheapest = current_cost;
        current = current->next;
    }
    if (cheapest.case_id == 1)
        execute_case_one(a, b, &cheapest, "pb");
    else if (cheapest.case_id == 2)
        execute_case_two(a, b, &cheapest, "pb");
    else if (cheapest.case_id == 3)
        execute_case_three(a, b, &cheapest, "pb");
    else
        execute_case_four(a, b, &cheapest, "pb");
}

void push_cheapest_to_a(t_stack *a, t_stack *b)
{
    t_cost cheapest;
    t_node *current;
    t_cost current_cost;
    
    current = b->head;
    cheapest.total_cost = INT_MAX;
    
    while (current)
    {
        calculate_cost_ba(a, b, current, &current_cost);
        if (current_cost.total_cost < cheapest.total_cost)
            cheapest = current_cost;
        current = current->next;
    }
    if (cheapest.case_id == 1)
        execute_case_one(a, b, &cheapest, "pa");
    else if (cheapest.case_id == 2)
        execute_case_two(a, b, &cheapest, "pa");
    else if (cheapest.case_id == 3)
        execute_case_three(a, b, &cheapest, "pa");
    else
        execute_case_four(a, b, &cheapest, "pa");
}

void mechanical_turk(t_stack *a, t_stack *b)
{
    seed_stack_b(a, b);
    while (a->size > 3)
    {
        push_cheapest_to_b(a, b);
    }
    sort_three(a, b);
    while (b->size > 0)
    {
        push_cheapest_to_a(a, b);
    }
    final_align_a(a);
}
