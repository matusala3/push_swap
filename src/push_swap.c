#include "../include/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	//t_node	*current;
	int *linkedlist_copy;

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
	if(!arr || low < 0 || high < 0)
		return;
	if (low < high)
	{
		int pivot = partition(arr, low, high);
		quick_sort(arr, low, pivot - 1);
		quick_sort(arr, pivot + 1, high);
	}
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

	if (!a || !b)
		return;
	if (a == b)
		return;
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
	if (high != median)
		swap(&arr[high], &arr[median]);
	i = low;
	j = low;
	while (i < high)
	{
		if(arr[i] < arr[high])
		{
			if (i != j)
				swap(&arr[i], &arr[j]);
			j++;
		}
		i++;
	}
	if(j != high)
		swap(&arr[j], &arr[high]);
	return (j);
}

// check duplicates in sorted array
bool check_duplicates(int *arr)
{
	int i;

	i = 0;
	while (arr[i + 1])
	{
		if (arr[i] == arr[i + 1])
			return (true);
		i++;
	}
	return (false);
}
