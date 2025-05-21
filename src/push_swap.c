#include "../include/parsing_utils.h"
#include "../include/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_node	*current;

	stack_a.head = NULL;
	stack_a.tail = NULL;
	stack_a.size = 0;
	if (argc == 1)
		return (0);
	printf("Program started with %d arguments:\n", argc - 1);
	if (!parse_input(argv, &stack_a))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	current = stack_a.head;
	printf("Stack A: \n head -> ");
	if (!current)
	{
		printf("(empty)");
	}
	else
	{
		while (current)
		{
			printf("[%d]", current->value);
			if (current->next)
				printf("and its next is %d ", current->next->value);
			else
				printf("has no next ");
			if (current->prev)
				printf("and its prev is %d ", current->prev->value);
			else
				printf("has no prev ");
			current = current->next;
		}
		printf(" <- tail");
	}
	free_stack(&stack_a);
	return (0);
}
int	*copy_stack_to_array(t_stack stack_a, int size)
{
	t_node	*current;
	int *arr;
	int i;
	
	arr = (int *)malloc(sizeof(int) * size);
	if (!arr)
		return NULL;
	current = stack_a.head;
	i = 0;
	while (i < size && current)
	{
		arr[i] = current->value;
		current = current->next;
		i++;
	}
	return arr;
}
