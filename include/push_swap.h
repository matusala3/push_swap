/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:31:13 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/11 16:39:54 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

typedef struct s_cost {
	t_node *target_node;      // Node in A to push
	int     index_stack_a;    // Position in A
	int     index_stack_b;    // Insertion position in B

	int     cost_top_a;       // Number of ops for A (ra/rra)
	int     cost_top_b;       // Number of ops for B (rb/rrb)

	char   *dir_a;            // "ra" or "rra"
	char   *dir_b;            // "rb" or "rrb"

	int     total_cost;       // Max(cost_top_a, cost_top_b) for aligned case
	int     case_id;          // 1 = case_one (ra + rb), 2 = case_two (rra + rrb)
} t_cost;



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
void	swap_stack(t_stack *stack);
void	rotate(t_stack *stack);
void	reverse_rotate(t_stack *stack);
void	pusha_to_b(t_stack *stack_a, t_stack *stack_b);
void	pushb_to_a(t_stack *stack_a, t_stack *stack_b);
int	execute_instruction(t_stack *a, t_stack *b, char *op);
void	swap_both(t_stack *a, t_stack *b);
void	rotate_both(t_stack *a, t_stack *b);
void	reverse_rotate_both(t_stack *a, t_stack *b);
int	ft_strcmp(char *s1, char *s2);

//sorts
bool is_sorted(t_stack *stack);
void sort_strategy(t_stack *stack_a, t_stack *stack_b);
void	small_sort(t_stack *a, t_stack *b);
void	sort_two_a(t_stack *a, t_stack *b);
void	sort_two_b(t_stack *a, t_stack *b);
void	sort_three(t_stack *a, t_stack *b);
void	sort_four_five(t_stack *a, t_stack *b);
void mechanical_turk(t_stack *a, t_stack *b);
void set_case_one_cost(t_cost *c, int a_cost, int b_cost);
void set_case_two_cost(t_cost *c, int rra_cost, int rrb_cost);
void calculate_cost_ab(t_stack *a, t_stack *b, t_node *node, t_cost *c);
int get_index_of_max(t_stack *b);
int find_place_in_b(t_stack *b, int value);
int get_node_index(t_stack *stack, t_node *target);
void seed_stack_b(t_stack *a, t_stack *b);
int find_place_in_a(t_stack *a, int value);

//addition remove after use
void print_stack(t_stack *stack);
#endif