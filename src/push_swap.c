/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:31:29 by magebreh          #+#    #+#             */
/*   Updated: 2025/05/30 15:23:22 by magebreh         ###   ########.fr       */
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
	printf("before sorting: ");
	print_stack(&stack_a);
	printf("\n");
	sort_strategy(&stack_a, &stack_b);
	printf("after sorting: ");
	print_stack(&stack_a);
	printf("\n");
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}

bool	parse_input(char **argv, t_stack *stack_a)
{
	int		i;
	bool	res;
	char	**splitted_arg;

	i = 1;
	while (argv[i])
	{
		splitted_arg = ft_split(argv[i], ' ');
		res = process_argv_entry(splitted_arg, stack_a);
		free_split_arg(splitted_arg);
		if (!res)
		{
			free_stack(stack_a);
			return (false);
		}
		i++;
	}
	return (true);
}

void sort_strategy(t_stack *stack_a, t_stack *stack_b)
{
	if (is_sorted(stack_a))
		return ;
	if (stack_a->size <= 5)
		small_sort(stack_a, stack_b);
	// else if (stack_a->size <= 500)
	// 	mechanical_turk(stack_a, stack_b);
	// else
	// 	radix_sort(stack_a, stack_b);
}

bool is_sorted(t_stack *stack)
{
	t_node *current;

	if (stack->size < 2)
		return true;
	current = stack->head;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return false;
		current = current->next;
	}
	return true;
}

void print_stack(t_stack *stack)
{
	int size;
	t_node *current;

	size = stack->size;
	current = stack->head;
	if(!size)
		return ;
	while (size)
	{
		printf("%d", current->value);
		current = current->next;
		size--;
	}
	
}