#include "../include/push_swap.h"

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

void heapify(int *arr, int size, int root)
{
	int largest;
    int left;
    int right;
	
	largest = root;
	left = (2*root)+1;
	right = (2*root)+2;
	if(left < size && arr[left] > arr[largest])
		largest = left;
	if(right < size && arr[right] > arr[largest])
		largest = right;
	if(largest != root)
	{
		swap(&arr[root], &arr[largest]);
		heapify(arr, size, largest);
	}
}