/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mechanical_turk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:48:07 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/23 13:52:02 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include <stdio.h>

t_node *get_node_at(t_stack *stack, int index)
{
    t_node *current;
    int i;
    
    current = stack->head;
    i = 0;
    
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

void set_case_three_cost(t_cost *c, int ra_cost, int rrb_cost, int total)
{
    c->cost_top_a = ra_cost;
    c->cost_top_b = rrb_cost;
    c->dir_a = "ra";
    c->dir_b = "rrb";
    c->total_cost = total;
    c->case_id = 3;
}

void set_case_four_cost(t_cost *c, int rra_cost, int rb_cost, int total)
{
    c->cost_top_a = rra_cost;
    c->cost_top_b = rb_cost;
    c->dir_a = "rra";
    c->dir_b = "rb";
    c->total_cost = total;
    c->case_id = 4;
}

void calculate_four_costs(t_stack *a, t_stack *b, t_cost *c, int costs[4])
{
    // Case 1: ra + rb (both rotate up)
    if (c->index_stack_a > c->index_stack_b) 
        costs[0] = c->index_stack_a;
    else
        costs[0] = c->index_stack_b;
    
    // Case 2: rra + rrb (both rotate down)
    if ((a->size - c->index_stack_a) > (b->size - c->index_stack_b))
        costs[1] = a->size - c->index_stack_a;
    else
        costs[1] = b->size - c->index_stack_b;
    
    // Case 3: ra + rrb (A up, B down)
    costs[2] = c->index_stack_a + (b->size - c->index_stack_b);
    
    // Case 4: rra + rb (A down, B up)
    costs[3] = (a->size - c->index_stack_a) + c->index_stack_b;
}

int find_best_case(int costs[4])
{
    int min_cost;
    int best_case;
    int i;
    
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
    return best_case;
}

void set_cost_by_case(t_stack *a, t_stack *b, t_cost *c, int best_case, int cost)
{
    if (best_case == 1)
    {
        set_case_one_cost(c, c->index_stack_a, c->index_stack_b);
    }
    else if (best_case == 2)
    {
        set_case_two_cost(c, a->size - c->index_stack_a, b->size - c->index_stack_b);
    }
    else if (best_case == 3)
    {
        set_case_three_cost(c, c->index_stack_a, b->size - c->index_stack_b, cost);
    }
    else
    {
        set_case_four_cost(c, a->size - c->index_stack_a, c->index_stack_b, cost);
    }
}

void calculate_cost_ab(t_stack *a, t_stack *b, t_node *node, t_cost *c)
{
    int costs[4];
    int best_case;

    c->target_node = node;
    c->index_stack_a = get_node_index(a, node);
    c->index_stack_b = find_place_in_b(b, node->value);
    
    calculate_four_costs(a, b, c, costs);
    best_case = find_best_case(costs);
    set_cost_by_case(a, b, c, best_case, costs[best_case - 1]);
}

void calculate_cost_ba(t_stack *a, t_stack *b, t_node *node, t_cost *c)
{
    int costs[4];
    int best_case;

    c->target_node = node;
    c->index_stack_b = get_node_index(b, node);
    c->index_stack_a = find_place_in_a(a, node->value);

    calculate_four_costs(a, b, c, costs);
    best_case = find_best_case(costs);
    set_cost_by_case(a, b, c, best_case, costs[best_case - 1]);
}

int get_index_of_min(t_stack *b)
{
    int min;
    int index;
    int i;
    t_node *current;

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
    return index;
}


int get_index_of_max(t_stack *s)
{
    int max;
    int index;
    int i;
    t_node *current;

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
    return index;
}

int get_index_between_b(t_stack *b, int value)
{
    t_node *current;
    int index;

    current = b->head;
    index = 0;

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
    t_node *current;
    int index;

    current = a->head;
    index = 0;

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
    int max_i;
    int min_i;
    t_node *max_node;
    t_node *min_node;

    max_i = get_index_of_max(b);
    min_i = get_index_of_min(b);
    
    max_node = get_node_at(b, max_i);
    min_node = get_node_at(b, min_i);
    if (max_node && value > max_node->value)
        return max_i;
    if (min_node && value < min_node->value)
        return min_i + 1;
    return get_index_between_b(b, value);
}

int find_place_in_a(t_stack *a, int value)
{
    int max_i;
    int min_i;
    t_node *max_node;
    t_node *min_node;

    max_i = get_index_of_max(a);
    min_i = get_index_of_min(a);
    max_node = get_node_at(a, max_i);
    min_node = get_node_at(a, min_i);

    if (value < min_node->value)
        return min_i;
    if (value > max_node->value)
        return max_i + 1;
    return get_index_between_a(a, value);
}


int get_node_index(t_stack *stack, t_node *target)
{
    int index;
    t_node *current;
    
    index = 0;
    current = stack->head;
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

void execute_case_three_ab(t_stack *a, t_stack *b, t_cost *c)
{
    // Case 3: ra + rrb (A rotates up, B rotates down)
    while (c->cost_top_a-- > 0)
        execute_instruction(a, b, "ra");
    while (c->cost_top_b-- > 0)
        execute_instruction(a, b, "rrb");
    execute_instruction(a, b, "pb");
}

void execute_case_four_ab(t_stack *a, t_stack *b, t_cost *c)
{
    // Case 4: rra + rb (A rotates down, B rotates up)
    while (c->cost_top_a-- > 0)
        execute_instruction(a, b, "rra");
    while (c->cost_top_b-- > 0)
        execute_instruction(a, b, "rb");
    execute_instruction(a, b, "pb");
}

void execute_case_three_ba(t_stack *a, t_stack *b, t_cost *c)
{
    // Case 3: ra + rrb (A rotates up, B rotates down)
    while (c->cost_top_a-- > 0)
        execute_instruction(a, b, "ra");
    while (c->cost_top_b-- > 0)
        execute_instruction(a, b, "rrb");
    execute_instruction(a, b, "pa");
}

void execute_case_four_ba(t_stack *a, t_stack *b, t_cost *c)
{
    // Case 4: rra + rb (A rotates down, B rotates up)
    while (c->cost_top_a-- > 0)
        execute_instruction(a, b, "rra");
    while (c->cost_top_b-- > 0)
        execute_instruction(a, b, "rb");
    execute_instruction(a, b, "pa");
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
        execute_case_one_ab(a, b, &cheapest);
    else if (cheapest.case_id == 2)
        execute_case_two_ab(a, b, &cheapest);
    else if (cheapest.case_id == 3)
        execute_case_three_ab(a, b, &cheapest);
    else
        execute_case_four_ab(a, b, &cheapest);
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
        execute_case_one_ba(a, b, &cheapest);
    else if (cheapest.case_id == 2)
        execute_case_two_ba(a, b, &cheapest);
    else if (cheapest.case_id == 3)
        execute_case_three_ba(a, b, &cheapest);
    else
        execute_case_four_ba(a, b, &cheapest);
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
