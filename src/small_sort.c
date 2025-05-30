/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:03:10 by magebreh          #+#    #+#             */
/*   Updated: 2025/05/30 01:51:33 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void sort_two(t_stack *a, t_stack *b)
{
	if (a->head->value > a->head->next->value)
		execute_instruction(a, b, "sa");
}


void	sort_three(t_stack *a, t_stack *b)
{
	int x = a->head->value;
	int y = a->head->next->value;
	int z = a->tail->value;

	if (x < y && y < z)
		return ;
	else if (x > y && y < z && x < z)
		execute_instruction(a, b, "sa");
	else if (x > y && y > z)
	{
		execute_instruction(a, b, "sa");
		execute_instruction(a, b, "rra");
	}
	else if (x > y && y < z && x > z)
		execute_instruction(a, b, "ra");
	else if (x < y && y > z && x < z)
	{
		execute_instruction(a, b, "sa");
		execute_instruction(a, b, "ra");
	}
	else if (x < y && y > z && x > z)
		execute_instruction(a, b, "rra");
}

// void	sort_four_five(t_stack *a, t_stack *b)
// {
	
// }

void	small_sort(t_stack *a, t_stack *b)
{
    if (a->size == 2)
        sort_two(a, b);
    else if (a->size == 3)
        sort_three(a, b);
    // else if (a->size <= 5)
    //     sort_four_five(a, b);
}
