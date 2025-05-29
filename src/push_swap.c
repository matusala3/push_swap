/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:31:29 by magebreh          #+#    #+#             */
/*   Updated: 2025/05/29 21:55:41 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;

	stack_a = (t_stack){NULL, NULL, 0};
	stack_b = (t_stack){NULL, NULL, 0};
	if (argc == 1)
		return (0);
	if (!parse_input(argv, &stack_a))
	{
		free_stack(&stack_a);
		write(2, "Error\n", 6);
		return (1);
	}
	if (check_duplicates(&stack_a))
	{
		free_stack(&stack_a);
		write(2, "Error\n", 6);
		return (1);
	}
	sort_strategy(stack_a, stack_b);
	free_stack(&stack_a);
	return (0);
}

void sort_strategy(t_stack stack_a, t_stack stack_b)
{
	
}