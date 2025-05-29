/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rotation_ops.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:31:19 by magebreh          #+#    #+#             */
/*   Updated: 2025/05/29 13:54:33 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	rotate(t_stack *stack)
{
	t_node	*current;

	if (stack->size < 2)
		return ;
	current = stack->head;
	stack->head = stack->head->next;
	stack->head->prev = NULL;
	current->next = NULL;
	current->prev = stack->tail;
	stack->tail->next = current;
	stack->tail = current;
}

void	rotate_both(t_stack *stack_a, t_stack *stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
}

void revers_rotate(t_stack *stack)
{
	t_node	*current;

	if (stack->size < 2)
    return ;
	current = stack->tail;
	stack->tail = stack->tail->prev;
	stack->tail->next = NULL;

	current->prev = NULL;
	current->next = stack->head;
	stack->head->prev = current;
	stack->head = current;
}

void	revers_rotate_both(t_stack *stack_a, t_stack *stack_b)
{
	revers_rotate(stack_a);
	revers_rotate(stack_b);
}