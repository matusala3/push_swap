/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:31:47 by magebreh          #+#    #+#             */
/*   Updated: 2025/05/30 13:24:36 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	quick_sort(int *arr, int low, int high)
{
	int	pivot;

	if (!arr || low < 0 || high < 0)
		return ;
	if (low < high)
	{
		pivot = partition(arr, low, high);
		quick_sort(arr, low, pivot - 1);
		quick_sort(arr, pivot + 1, high);
	}
}

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

void	heap_sort(int *arr, int size)
{
	int	i;

	i = size / 2 - 1;
	while (i >= 0)
	{
		heapify(arr, size, i);
		i--;
	}
	i = size - 1;
	while (i > 0)
	{
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
		i--;
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
	if (size < 15 && size > 2)
		quick_sort(linkedlist_copy, 0, size - 1);
	else if (size < 250 && size > 15)
		insertion_sort(linkedlist_copy, size);
	else
		heap_sort(linkedlist_copy, size);
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
