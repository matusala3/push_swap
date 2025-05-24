#include "../include/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	int *linkedlist_copy;

	stack_a.head = NULL;
	stack_a.tail = NULL;
	stack_a.size = 0;
	if (argc == 1)
		return (0);
	if (!parse_input(argv, &stack_a))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	linkedlist_copy = copy_stack_to_array(stack_a, stack_a.size);
	quick_sort(linkedlist_copy, 0, stack_a.size - 1);
	if(check_duplicates(linkedlist_copy))
	{
		write(2, "Error\n", 6);
		free(linkedlist_copy);
		free_stack(&stack_a);
		return (1);
	}
	free(linkedlist_copy);
	free_stack(&stack_a);
	return (0);
}
