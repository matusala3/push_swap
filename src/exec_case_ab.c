/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_case_ab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:04:25 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/23 18:21:49 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	execute_case_one(t_stack *a, t_stack *b, t_cost *c, char *push_op)
{
	int	common;
	int	extra_a;
	int	extra_b;

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
	execute_instruction(a, b, push_op);
}

void	execute_case_two(t_stack *a, t_stack *b, t_cost *c, char *push_op)
{
	int	common;
	int	extra_a;
	int	extra_b;

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
	execute_instruction(a, b, push_op);
}

void	execute_case_three(t_stack *a, t_stack *b, t_cost *c, char *push_op)
{
	while (c->cost_top_a-- > 0)
		execute_instruction(a, b, "ra");
	while (c->cost_top_b-- > 0)
		execute_instruction(a, b, "rrb");
	execute_instruction(a, b, push_op);
}

void	execute_case_four(t_stack *a, t_stack *b, t_cost *c, char *push_op)
{
	while (c->cost_top_a-- > 0)
		execute_instruction(a, b, "rra");
	while (c->cost_top_b-- > 0)
		execute_instruction(a, b, "rb");
	execute_instruction(a, b, push_op);
}
