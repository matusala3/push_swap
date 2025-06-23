/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cases.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:34:47 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/23 18:35:44 by magebreh         ###   ########.fr       */
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
