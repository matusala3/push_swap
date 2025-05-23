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

bool safe_atoi(const char *str, int *out);
bool parse_input(char **argv, t_stack *stack_a);
bool process_argv_entry(char **splitted_arg, t_stack *stack_a);
bool stack_append(t_stack *stack_a, int val);
void free_stack(t_stack *stack);
void free_split_arg(char **split);
int *copy_stack_to_array(t_stack stack_a, int size);
void quick_sort(int *arr, int low, int high);
int partition(int *arr, int low, int high);
int median_of_three(int *arr, int low, int high);
void swap(int *a, int *b);
bool check_duplicates(int *arr);

#endif