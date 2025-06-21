/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mechanical_turk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:48:07 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/21 12:44:37 by magebreh         ###   ########.fr       */
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


void set_case_two_cost(t_cost *c, int rra, int rrb)
{
    c->dir_a = "rra";
    c->dir_b = "rrb";
    c->combo_op = "rrr";
    c->cost_top_a = rra;
    c->cost_top_b = rrb;
    
    if (rra > rrb)
        c->total_cost = rra;
    else
        c->total_cost = rrb;
    
    c->case_id = 2;
}

void set_case_one_cost(t_cost *c, int ra, int rb)
{
    c->dir_a = "ra";
    c->dir_b = "rb";
    c->combo_op = "rr";
    c->cost_top_a = ra;
    c->cost_top_b = rb;
    
    if (ra > rb)
        c->total_cost = ra;
    else
        c->total_cost = rb;
    
    c->case_id = 1;
}

void set_case_swap_cost(t_cost *c, int swap_a, int swap_b)
{
    if (swap_a && swap_b)
    {
        c->dir_a = NULL;
        c->dir_b = NULL;
        c->combo_op = "ss";
    }
    else if (swap_a)
    {
        c->dir_a = "sa";
        c->dir_b = NULL;
        c->combo_op = NULL;
    }
    else if (swap_b)
    {
        c->dir_a = NULL;
        c->dir_b = "sb";
        c->combo_op = NULL;
    }

    c->cost_top_a = swap_a ? 1 : 0;
    c->cost_top_b = swap_b ? 1 : 0;
    c->total_cost = 1;
    c->case_id = 3;
}
void execute_case_mixed_ab(t_stack *a, t_stack *b, t_cost *c)
{
	int i;
	int pushed;

	if (!a || !b || !c)
		return;

	// Perform A's rotations (ra or rra)
	for (i = 0; i < c->cost_top_a; i++)
		execute_instruction(a, b, c->dir_a);

	// Perform B's rotations (rb or rrb)
	for (i = 0; i < c->cost_top_b; i++)
		execute_instruction(a, b, c->dir_b);

	if (a->head)
		pushed = a->head->value;
	else
		pushed = -999;  // Debug fallback

	execute_instruction(a, b, "pb");

}

// Step 1: Calculate indices for both stacks
void calculate_indices(t_stack *a, t_stack *b, t_node *node, t_cost *c)
{
    c->index_stack_a = get_node_index(a, node);
    c->index_stack_b = find_place_in_b(b, node->value);
}

// Step 2: Calculate direction and cost for stack A
void calculate_direction_cost_a(t_stack *a, t_cost *c)
{
    if (c->index_stack_a <= a->size / 2)
    {
        c->dir_a = "ra";
        c->cost_top_a = c->index_stack_a;
    }
    else
    {
        c->dir_a = "rra";
        c->cost_top_a = a->size - c->index_stack_a;
    }
}

// Step 3: Calculate direction and cost for stack B
void calculate_direction_cost_b(t_stack *b, t_cost *c)
{
    if (c->index_stack_b == 0)
    {
        // Element goes to top of B (new maximum)
        c->dir_b = NULL;
        c->cost_top_b = 0;
    }
    else if (c->index_stack_b == b->size)
    {
        // Element goes to bottom of B (new minimum)
        // Will need one rb after pb to put it at bottom
        c->dir_b = NULL;
        c->cost_top_b = 0;
        c->combo_op = NULL;
        c->case_id = 3;
    }
    else
    {
        // Element goes between existing elements
        if (c->index_stack_b <= b->size / 2)
        {
            c->dir_b = "rb";
            c->cost_top_b = c->index_stack_b;
        }
        else
        {
            c->dir_b = "rrb";
            c->cost_top_b = b->size - c->index_stack_b;
        }
    }
}


// Step 5: Check for overlapping rotation directions and optimize
void optimize_rotations(t_cost *c)
{
    if (c->dir_a == NULL || c->dir_b == NULL)
    {
        c->combo_op = NULL;
        c->total_cost = c->cost_top_a + c->cost_top_b;
        c->case_id = 3;
        return;
    }

    // Check if both are "ra" and "rb" (can use "rr")
    if (c->dir_a[0] == 'r' && c->dir_a[1] == 'a' && 
        c->dir_b[0] == 'r' && c->dir_b[1] == 'b')
    {
        c->combo_op = "rr";
        c->case_id = 1;
        if (c->cost_top_a > c->cost_top_b)
            c->total_cost = c->cost_top_a;
        else
            c->total_cost = c->cost_top_b;
    }
    // Check if both are "rra" and "rrb" (can use "rrr")
    else if (c->dir_a[0] == 'r' && c->dir_a[1] == 'r' && c->dir_a[2] == 'a' &&
             c->dir_b[0] == 'r' && c->dir_b[1] == 'r' && c->dir_b[2] == 'b')
    {
        c->combo_op = "rrr";
        c->case_id = 2;
        if (c->cost_top_a > c->cost_top_b)
            c->total_cost = c->cost_top_a;
        else
            c->total_cost = c->cost_top_b;
    }
    else
    {
        c->combo_op = NULL;
        c->total_cost = c->cost_top_a + c->cost_top_b;
        c->case_id = 3;
    }
}



// Step 6: Add final push operation cost
void add_push_cost(t_cost *c, int b_size)
{
    c->total_cost += 1; // Always count pb
    
    // Add extra rb cost if element is new minimum
    if (c->index_stack_b == b_size && b_size > 0)
        c->total_cost += 1;
}

void case_three(t_stack *a, t_stack *b, t_cost *c)
{
    while (c->cost_top_a-- > 0)
    {
        if (c->dir_a && c->dir_a[0] == 'r' && c->dir_a[1] == 'a')
            execute_instruction(a, b, "ra");
        else
            execute_instruction(a, b, "rra");
    }

    while (c->cost_top_b-- > 0)
    {
        if (c->dir_b && c->dir_b[0] == 'r' && c->dir_b[1] == 'b')
            execute_instruction(a, b, "rb");
        else
            execute_instruction(a, b, "rrb");
    }
}


void case_two(t_stack *a, t_stack *b, t_cost *c)
{
    int shared;
    int remaining_a;
    int remaining_b;

    shared = c->cost_top_a;
    if (c->cost_top_b < c->cost_top_a)
        shared = c->cost_top_b;
    remaining_a = c->cost_top_a - shared;
    remaining_b = c->cost_top_b - shared;
    while (shared-- > 0)
        execute_instruction(a, b, "rrr");

    while (remaining_a-- > 0)
        execute_instruction(a, b, "rra");

    while (remaining_b-- > 0)
        execute_instruction(a, b, "rrb");
}

void case_one(t_stack *a, t_stack *b, t_cost *c)
{
    int shared;
    int remaining_a;
    int remaining_b;

    shared = c->cost_top_a;
    if (c->cost_top_b < shared)
        shared = c->cost_top_b;
    remaining_a = c->cost_top_a - shared;
    remaining_b = c->cost_top_b - shared;

    while (shared-- > 0)
        execute_instruction(a, b, "rr");

    while (remaining_a-- > 0)
        execute_instruction(a, b, "ra");

    while (remaining_b-- > 0)
        execute_instruction(a, b, "rb");
}


void execute_push_ab(t_stack *a, t_stack *b, t_cost *c)
{
    int is_new_min = (c->index_stack_b == b->size);
    
    if (c->case_id == 1)
        case_one(a, b, c);
    else if (c->case_id == 2)
        case_two(a, b, c);
    else
        case_three(a, b, c);

    execute_instruction(a, b, "pb");

    // Special case: if element is new minimum (goes to bottom of B)
    // we need one rb after pb to put it at the bottom
    if (is_new_min && b->size > 1)
        execute_instruction(a, b, "rb");
}


// Main function - now much cleaner and more readable
void calculate_cost_ab(t_stack *a, t_stack *b, t_node *node, t_cost *c)
{
    c->target_node = node;
    calculate_indices(a, b, node, c);
    
    // Calculate costs for all four cases
    int ra = c->index_stack_a;
    int rb = c->index_stack_b;
    int rra = a->size - c->index_stack_a;
    int rrb = b->size - c->index_stack_b;
    
    // Special case: if element goes to top of B (new max), no B rotation needed
    if (c->index_stack_b == 0)
    {
        rb = 0;
        rrb = 0;
    }
    
    // Case 1: ra + rb (can use rr)
    int cost1 = (ra > rb) ? ra : rb;
    
    // Case 2: rra + rrb (can use rrr)
    int cost2 = (rra > rrb) ? rra : rrb;
    
    // Case 3: ra + rrb (no combo)
    int cost3 = ra + rrb;
    
    // Case 4: rra + rb (no combo)
    int cost4 = rra + rb;
    
    // Find minimum cost
    int min_cost = cost1;
    int best_case = 1;
    
    if (cost2 < min_cost) {
        min_cost = cost2;
        best_case = 2;
    }
    if (cost3 < min_cost) {
        min_cost = cost3;
        best_case = 3;
    }
    if (cost4 < min_cost) {
        min_cost = cost4;
        best_case = 4;
    }
    
    // Set the cost structure based on best case
    if (best_case == 1) {
        c->dir_a = "ra";
        c->dir_b = (rb > 0) ? "rb" : NULL;
        c->cost_top_a = ra;
        c->cost_top_b = rb;
        c->combo_op = (rb > 0) ? "rr" : NULL;
        c->case_id = 1;
        c->total_cost = cost1;
    }
    else if (best_case == 2) {
        c->dir_a = "rra";
        c->dir_b = (rrb > 0) ? "rrb" : NULL;
        c->cost_top_a = rra;
        c->cost_top_b = rrb;
        c->combo_op = (rrb > 0) ? "rrr" : NULL;
        c->case_id = 2;
        c->total_cost = cost2;
    }
    else if (best_case == 3) {
        c->dir_a = "ra";
        c->dir_b = (rrb > 0) ? "rrb" : NULL;
        c->cost_top_a = ra;
        c->cost_top_b = rrb;
        c->combo_op = NULL;
        c->case_id = 3;
        c->total_cost = cost3;
    }
    else {
        c->dir_a = "rra";
        c->dir_b = (rb > 0) ? "rb" : NULL;
        c->cost_top_a = rra;
        c->cost_top_b = rb;
        c->combo_op = NULL;
        c->case_id = 3;
        c->total_cost = cost4;
    }
    
    // Add push cost
    add_push_cost(c, b->size);
}

int max(int a, int b)
{
    return ((a > b) * a + (a <= b) * b);
}




void calculate_cost_ba(t_stack *a, t_stack *b, t_node *node, t_cost *c)
{
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


int get_index_of_min(t_stack *s)
{
    if (!s || !s->head)
        return 0;
    int min = s->head->value;
    int index = 0, i = 1;
    t_node *current = s->head->next;

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
    if (!s || !s->head)
        return 0;
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

int get_index_between_b(t_stack *s, int value)
{
    t_node *current = s->head;
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

static void	get_min_max(t_stack *b, int *min, int *max)
{
	t_node	*cur;

	*min = b->head->value;
	*max = b->head->value;
	cur = b->head;
	while (cur)
	{
		if (cur->value < *min)
			*min = cur->value;
		if (cur->value > *max)
			*max = cur->value;
		cur = cur->next;
	}
}

static int	find_between_nodes(t_stack *b, int value)
{
	t_node	*cur;
	int		i;

	cur = b->head;
	i = 0;
	while (cur && cur->next)
	{
		if (cur->value > value && value > cur->next->value)
			return (i + 1);
		cur = cur->next;
		i++;
	}
	return (-1);
}

int	find_place_in_b(t_stack *b, int value)
{
	int	min;
	int	max;
	int	pos;

	if (!b || !b->head || b->size == 0)
		return (0);
	if (b->size == 1)
	{
		if (value > b->head->value)
			return (0);
		else
			return (1);
	}
	get_min_max(b, &min, &max);
	if (value > max)
		return (0);
	if (value < min)
		return (b->size);
	pos = find_between_nodes(b, value);
	if (pos != -1)
		return (pos);
	if (b->tail->value > value && value > b->head->value)
		return (0);
	return (b->size);
}



int find_place_in_a(t_stack *a, int value)
{
    // Empty stack - insert at position 0
    if (!a || a->size == 0)
        return 0;
        
    // Find min and max values and their indices
    int min_val = a->head->value;
    int max_val = a->head->value;
    int min_idx = 0;
    int max_idx = 0;
    t_node *current = a->head;
    int i = 0;
    
    while (current)
    {
        if (current->value < min_val)
        {
            min_val = current->value;
            min_idx = i;
        }
        if (current->value > max_val)
        {
            max_val = current->value;
            max_idx = i;
        }
        current = current->next;
        i++;
    }
    
    // If value is smaller than min, it goes before min
    if (value < min_val)
        return min_idx;
    
    // If value is larger than max, it goes after max
    if (value > max_val)
        return (max_idx + 1) % a->size;
    
    // Find position between two values
    current = a->head;
    i = 0;
    while (current)
    {
        t_node *next = current->next ? current->next : a->head;
        if (current->value < value && value < next->value)
            return (i + 1) % a->size;
        current = current->next;
        i++;
    }
    
    return 0;
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
        execute_instruction(a, b, c->combo_op);
    while (extra_a-- > 0)
        execute_instruction(a, b, c->dir_a);
    while (extra_b-- > 0)
        execute_instruction(a, b, c->dir_b);
    execute_instruction(a, b, "pb");
}

void execute_case_swap_ab(t_stack *a, t_stack *b, t_cost *c)
{
    if (c->combo_op)
        execute_instruction(a, b, c->combo_op); // "ss"
    else
    {
        if (c->dir_a)
            execute_instruction(a, b, c->dir_a); // "sa"
        if (c->dir_b)
            execute_instruction(a, b, c->dir_b); // "sb"
    }
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
        execute_instruction(a, b, c->combo_op);
    while (extra_a-- > 0)
        execute_instruction(a, b, c->dir_a);
    while (extra_b-- > 0)
        execute_instruction(a, b, c->dir_b);
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
    
    // Phase 1: Initial setup - seed stack B
    seed_stack_b(a, b);
    
    // Phase 1: Push from A to B (maintaining descending order in B)
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
        execute_push_ab(a, b, &cheapest);
    }
    
    // Phase 2: Sort the remaining 3 elements in A
    sort_three(a, b);
    
    // Phase 3: Push everything back from B to A
    // Optimized version - no need to search, just push from top
    while (b->size > 0)
    {
        // Find where B's top element should go in A
        int target_pos = find_place_in_a(a, b->head->value);
        
        // Rotate A to bring target position to top
        if (target_pos == 0)
        {
            // Already at correct position
        }
        else if (target_pos <= a->size / 2)
        {
            while (target_pos-- > 0)
                execute_instruction(a, b, "ra");
        }
        else
        {
            int rotations = a->size - target_pos;
            while (rotations-- > 0)
                execute_instruction(a, b, "rra");
        }
        
        // Push from B to A
        execute_instruction(a, b, "pa");
    }
    
    // Final alignment: rotate A to put smallest element at top
    final_align_a(a);
}

