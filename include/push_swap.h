/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:31:13 by magebreh          #+#    #+#             */
/*   Updated: 2025/05/29 15:45:06 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef struct s_node {
	int             value;
	struct s_node  *prev;
	struct s_node  *next;
} t_node;

typedef struct s_stack {
	t_node  *head;
	t_node  *tail;
	int      size;
} t_stack;


//parsing functions
void free_stack(t_stack *stack);
void free_split_arg(char **split);
bool safe_atoi(const char *str, int *out);
bool stack_append(t_stack *stack_a, int val);
bool parse_input(char **argv, t_stack *stack_a);
bool process_argv_entry(char **splitted_arg, t_stack *stack_a);

//checking duplication with sorting
void quick_sort(int *arr, int low, int high);
void insertion_sort(int *arr, int size);
int	*copy_stack_to_array(t_stack stack_a, int size);
bool check_duplicates(t_stack *stack_a);
int median_of_three(int *arr, int low, int high);
void swap(int *a, int *b);
int partition(int *arr, int low, int high);
void heapify(int *arr, int size, int root);
void heap_sort(int *arr, int size);

//operations
void swap_nodes(t_stack *stack_a, t_stack *stack_b);

#endif