#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	//t_node	*current;
	int *linkedlist_copy;
	int i = 0;

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
	// current = stack_a.head;
	// printf("Stack A: \n head -> ");
	// if (!current)
	// {
	// 	printf("(empty)");
	// }
	// else
	// {
	// 	while (current)
	// 	{
	// 		printf("[%d]", current->value);
	// 		if (current->next)
	// 			printf("and its next is %d ", current->next->value);
	// 		else
	// 			printf("has no next ");
	// 		if (current->prev)
	// 			printf("and its prev is %d ", current->prev->value);
	// 		else
	// 			printf("has no prev ");
	// 		current = current->next;
	// 	}
	// 	printf(" <- tail");
	// }


	// linkedlist_copy = copy_stack_to_array(stack_a, stack_a.size);
	// while (stack_a.size > i)
	// {
	// 	printf("arr[%d] = %d \n", i, linkedlist_copy[i]);
	// 	i++;
	// }
	// free(linkedlist_copy);


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

void quick_sort(int *arr, int low, int high)
{

}

int median_of_three(int *arr, int low, int high)
{
	int mid;
	
	mid = (low + high) / 2;
	int a = arr[low];
	int b = arr[mid];
	int c = arr[high];
	if((a < b && b < c) ||(c < b && b < a))
		return(mid);
	else if((b < a && a < c) || (c < a && a < b))
		return (low);
	else
		return (high);
}

void swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int *arr, int low, int high)
{
	int median;
	int i;
	int j;

	median = median_of_three(arr, low, high);
	swap(&arr[high], &arr[median]);
	i = low;
	j = low;
	while (i < high)
	{
		if(arr[i] < arr[high])
		{
			swap(&arr[i], &arr[j]);
			j++;
		}
		i++;
	}
	swap(&arr[j], &arr[high]);
	return (j);
}
