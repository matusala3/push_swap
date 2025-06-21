/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:31:23 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/19 00:23:49 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	swap_stack(t_stack *stack)
{
	t_node	*current;

	if (stack->size < 2)
		return ;
	current = stack->head;
	stack->head = current->next;
	stack->head->prev = NULL;
	current->next = stack->head->next;
	if (current->next != NULL)
		current->next->prev = current;
	stack->head->next = current;
	current->prev = stack->head;
	if (stack->size == 2)
		stack->tail = current;
}

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

void	reverse_rotate(t_stack *stack)
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

void	pusha_to_b(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*current;

	if (stack_a->size == 0)
		return ;
	current = stack_a->head;
	stack_a->head = current->next;
	if (stack_a->head != NULL)
		stack_a->head->prev = NULL;
	else
		stack_a->tail = NULL;
	stack_a->size--;
	current->next = stack_b->head;
	current->prev = NULL;
	if (stack_b->head != NULL)
		stack_b->head->prev = current;
	stack_b->head = current;
	if (stack_b->size == 0)
		stack_b->tail = current;
	stack_b->size++;
}

void	pushb_to_a(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*current;

	if (stack_b->size == 0)
		return ;
	current = stack_b->head;
	stack_b->head = current->next;
	if (stack_b->head != NULL)
		stack_b->head->prev = NULL;
	else
		stack_b->tail = NULL;
	stack_b->size--;
	current->next = stack_a->head;
	current->prev = NULL;
	if (stack_a->head != NULL)
		stack_a->head->prev = current;
	stack_a->head = current;
	if (stack_a->size == 0)
		stack_a->tail = current;
	stack_a->size++;
}
