#include "../include/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;

	stack_a = (t_stack) {NULL, NULL, 0};
	if (argc == 1)
		return (0);
	if (!parse_input(argv, &stack_a))
	{
		free_stack(&stack_a);
		write(2, "Error\n", 6);
		return (1);
	}
	if(check_duplicates(&stack_a))
	{
		free_stack(&stack_a);
		write(2, "Error\n", 6);
		return (1);
	}
	free_stack(&stack_a);
	return (0);
}
