/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_duplicates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:00:00 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/26 19:31:35 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/checker_bonus.h"

void	insertion_sort(int *arr, int size)
{
	int	i;
	int	j;
	int	key;

	i = 0;
	j = 0;
	while (i < size)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
		i++;
	}
}

void	swap_int(int *a, int *b)
{
	int	temp;

	if (!a || !b)
		return ;
	if (a == b)
		return ;
	temp = *a;
	*a = *b;
	*b = temp;
}

void	heapify(int *arr, int size, int root)
{
	int	largest;
	int	left;
	int	right;

	largest = root;
	left = (2 * root) + 1;
	right = (2 * root) + 2;
	if (left < size && arr[left] > arr[largest])
		largest = left;
	if (right < size && arr[right] > arr[largest])
		largest = right;
	if (largest != root)
	{
		swap_int(&arr[root], &arr[largest]);
		heapify(arr, size, largest);
	}
}

int	*copy_stack_to_array(t_stack stack_a, int size)
{
	t_node	*current;
	int		*arr;
	int		i;

	arr = (int *)malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	current = stack_a.head;
	i = 0;
	while (i < size && current)
	{
		arr[i] = current->value;
		current = current->next;
		i++;
	}
	return (arr);
}

bool	check_duplicates(t_stack *stack_a)
{
	int	*linkedlist_copy;
	int	size;

	size = stack_a->size;
	if (stack_a->size < 2)
		return (false);
	linkedlist_copy = copy_stack_to_array(*stack_a, stack_a->size);
	if (!linkedlist_copy)
		return (false);
	insertion_sort(linkedlist_copy, size);
	while (size > 1)
	{
		if (linkedlist_copy[size - 1] == linkedlist_copy[size - 2])
		{
			free(linkedlist_copy);
			return (true);
		}
		size--;
	}
	free(linkedlist_copy);
	return (false);
}
