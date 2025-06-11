/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mechanical_turk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:48:07 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/11 18:23:17 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include <stdio.h>

t_node *get_node_at(t_stack *stack, int index)
{
    t_node *current = stack->head;
    int i = 0;
    
    while (current && i < index)
    {
        current = current->next;
        i++;
    }
    return current;
}

void set_case_one_cost(t_cost *c, int a_cost, int b_cost)
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

void set_case_two_cost(t_cost *c, int rra_cost, int rrb_cost)
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

void calculate_cost_ab(t_stack *a, t_stack *b, t_node *node, t_cost *c)
{
    int ra;
    int rb;
    int rra;
    int rrb;
    int cost_case_one;
    int cost_case_two;

    c->target_node = node;
    c->index_stack_a = get_node_index(a, node);
    c->index_stack_b = find_place_in_b(b, node->value);
    ra = c->index_stack_a;
    rb = c->index_stack_b;
    rra = a->size - ra;
    rrb = b->size - rb;
    if (ra > rb) 
        cost_case_one =  ra;
    else
        cost_case_one = rb;
    if (rra > rrb)
        cost_case_two = rra;
    else
        cost_case_two = rrb;
    if (cost_case_one <= cost_case_two)
        set_case_one_cost(c, ra, rb);
    else
        set_case_two_cost(c, rra, rrb);
}

void calculate_cost_ba(t_stack *a, t_stack *b, t_node *node, t_cost *c)
{
    c->target_node = node;
    c->index_stack_b = get_node_index(b, node);
    c->index_stack_a = find_place_in_a(a, node->value);
    int ra = c->index_stack_a;
    int rb = c->index_stack_b;
    int rra = a->size - ra;
    int rrb = b->size - rb;

    int cost_case_one = (ra > rb) ? ra : rb;
    int cost_case_two = (rra > rrb) ? rra : rrb;

    if (cost_case_one <= cost_case_two)
        set_case_one_cost(c, ra, rb);
    else
        set_case_two_cost(c, rra, rrb);
}


int get_index_of_min(t_stack *b)
{
    int min = b->head->value;
    int index = 0, i = 1;
    t_node *current = b->head->next;

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
    return index;
}


int get_index_of_max(t_stack *s)
{
    int max = s->head->value;
    int index = 0, i = 0;
    t_node *current = s->head;

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
    return index;
}

int get_index_between_b(t_stack *b, int value)
{
    t_node *current = b->head;
    int index = 0;

    while (current && current->next)
    {
        if (current->value > value && current->next->value < value)
            return index + 1;
        current = current->next;
        index++;
    }
    return 0;
}

int get_index_between_a(t_stack *a, int value)
{
    t_node *current = a->head;
    int index = 0;

    while (current && current->next)
    {
        if (current->value < value && current->next->value > value)
            return index + 1;
        current = current->next;
        index++;
    }
    return 0;
}

int find_place_in_b(t_stack *b, int value)
{
    int max_i = get_index_of_max(b);
    int min_i = get_index_of_min(b);
    
    t_node *max_node = get_node_at(b, max_i);
    t_node *min_node = get_node_at(b, min_i);
    if (max_node && value > max_node->value)
        return max_i;
    if (min_node && value < min_node->value)
        return min_i + 1;
    return get_index_between_b(b, value);
}

int find_place_in_a(t_stack *a, int value)
{
    int max_i = get_index_of_max(a);
    int min_i = get_index_of_min(a);
    t_node *max_node = get_node_at(a, max_i);
    t_node *min_node = get_node_at(a, min_i);

    if (value < min_node->value)
        return min_i;
    if (value > max_node->value)
        return max_i + 1;
    return get_index_between_a(a, value);
}


int get_node_index(t_stack *stack, t_node *target)
{
    int index = 0;
    t_node *current = stack->head;
    while (current && current != target)
    {
        index++;
        current = current->next;
    }
    return index;
}

void seed_stack_b(t_stack *a, t_stack *b)
{
	execute_instruction(a, b, "pb");
	execute_instruction(a, b, "pb");
    
    sort_two_b(a, b);
}

void execute_case_one_ab(t_stack *a, t_stack *b, t_cost *c)
{
    int common;
    int extra_a;
    int extra_b;

    if (c->cost_top_a < c->cost_top_b)
        common = c->cost_top_a;
    else
        common = c->cost_top_b;
    extra_a = c->cost_top_a - common;
    extra_b = c->cost_top_b - common;
    while (common-- > 0)
        execute_instruction(a, b, "rr");
    while (extra_a-- > 0)
        execute_instruction(a, b, "ra");
    while (extra_b-- > 0)
        execute_instruction(a, b, "rb");
    execute_instruction(a, b, "pb");
}

void execute_case_two_ab(t_stack *a, t_stack *b, t_cost *c)
{
    int common;
    int extra_a;
    int extra_b;

    if (c->cost_top_a < c->cost_top_b)
        common = c->cost_top_a;
    else
        common = c->cost_top_b;
    extra_a = c->cost_top_a - common;
    extra_b = c->cost_top_b - common;
    while (common-- > 0)
        execute_instruction(a, b, "rrr");
    while (extra_a-- > 0)
        execute_instruction(a, b, "rra");
    while (extra_b-- > 0)
        execute_instruction(a, b, "rrb");
    execute_instruction(a, b, "pb");
}

void execute_case_one_ba(t_stack *a, t_stack *b, t_cost *c)
{
    int common;
    int extra_a;
    int extra_b;

    if (c->cost_top_a < c->cost_top_b)
        common = c->cost_top_a;
    else
        common = c->cost_top_b;
    extra_a = c->cost_top_a - common;
    extra_b = c->cost_top_b - common;
    while (common-- > 0)
        execute_instruction(a, b, "rr");
    while (extra_a-- > 0)
        execute_instruction(a, b, "ra");
    while (extra_b-- > 0)
        execute_instruction(a, b, "rb");
    execute_instruction(a, b, "pa");
}

void execute_case_two_ba(t_stack *a, t_stack *b, t_cost *c)
{
    int common;
    int extra_a;
    int extra_b;

    if (c->cost_top_a < c->cost_top_b)
        common = c->cost_top_a;
    else 
        common = c->cost_top_b;
    extra_a = c->cost_top_a - common;
    extra_b = c->cost_top_b - common;
    while (common-- > 0)
        execute_instruction(a, b, "rrr");
    while (extra_a-- > 0)
        execute_instruction(a, b, "rra");
    while (extra_b-- > 0)
        execute_instruction(a, b, "rrb");
    execute_instruction(a, b, "pa");
}

void final_align_a(t_stack *a)
{
    int min_index = get_index_of_min(a);

    if (min_index <= a->size / 2)
    {
        while (min_index-- > 0)
            execute_instruction(a, NULL, "ra");
    }
    else
    {
        int r = a->size - min_index;
        while (r-- > 0)
            execute_instruction(a, NULL, "rra");
    }
}

void mechanical_turk(t_stack *a, t_stack *b)
{
    t_cost cheapest;
    t_node *current;
    t_cost current_cost;
    
    seed_stack_b(a, b);
    while (a->size > 3)
    {
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
            execute_case_one_ab(a, b, &cheapest);
        else
            execute_case_two_ab(a, b, &cheapest);
    }
    sort_three(a, b);
    while (b->size > 0)
    {
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
            execute_case_one_ba(a, b, &cheapest);
        else
            execute_case_two_ba(a, b, &cheapest);
    }
    final_align_a(a);
}

