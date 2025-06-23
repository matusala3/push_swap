/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:31:13 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/23 18:22:42 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct s_node {
	int				value;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_stack {
	t_node	*head;
	t_node	*tail;
	int		size;
}	t_stack;

typedef struct s_cost {
	t_node	*target_node;
	int		index_stack_a;
	int		index_stack_b;
	int		cost_top_a;
	int		cost_top_b;
	char	*dir_a;
	char	*dir_b;
	char	*combo_op;
	int		total_cost;
	int		case_id;
}	t_cost;

//parsing functions
void	free_stack(t_stack *stack);
void	free_split_arg(char **split);
bool	safe_atoi(const char *str, int *out);
bool	stack_append(t_stack *stack_a, int val);
bool	parse_input(char **argv, t_stack *stack_a);
bool	process_argv_entry(char **splitted_arg, t_stack *stack_a);

//checking duplication with sorting
void	quick_sort(int *arr, int low, int high);
void	insertion_sort(int *arr, int size);
int		*copy_stack_to_array(t_stack stack_a, int size);
bool	check_duplicates(t_stack *stack_a);
int		median_of_three(int *arr, int low, int high);
void	swap(int *a, int *b);
int		partition(int *arr, int low, int high);
void	heapify(int *arr, int size, int root);
void	heap_sort(int *arr, int size);

//operations
void	swap_stack(t_stack *stack);
void	rotate(t_stack *stack);
void	reverse_rotate(t_stack *stack);
void	pusha_to_b(t_stack *stack_a, t_stack *stack_b);
void	pushb_to_a(t_stack *stack_a, t_stack *stack_b);
int		execute_instruction(t_stack *a, t_stack *b, char *op);
void	swap_both(t_stack *a, t_stack *b);
void	rotate_both(t_stack *a, t_stack *b);
void	reverse_rotate_both(t_stack *a, t_stack *b);
int		ft_strcmp(char *s1, char *s2);

//sorts
bool	is_sorted(t_stack *stack);
void	sort_strategy(t_stack *stack_a, t_stack *stack_b);
void	small_sort(t_stack *a, t_stack *b);
void	sort_two(t_stack *a, t_stack *b, char stack);
void	sort_three(t_stack *a, t_stack *b);
void	sort_four_five(t_stack *a, t_stack *b);
void	mechanical_turk(t_stack *a, t_stack *b);
void	set_case_one_cost(t_cost *c, int a_cost, int b_cost);
void	set_case_two_cost(t_cost *c, int rra_cost, int rrb_cost);
void	calculate_cost_ab(t_stack *a, t_stack *b, t_node *node, t_cost *c);
int		get_index_of_max(t_stack *b);
int		find_place_in_b(t_stack *b, int value);
int		get_node_index(t_stack *stack, t_node *target);
void	seed_stack_b(t_stack *a, t_stack *b);
int		find_place_in_a(t_stack *a, int value);

// cost_calculation.c
void	calculate_cost_ba(t_stack *a, t_stack *b, t_node *node, t_cost *c);
void	calculate_cost_ab(t_stack *a, t_stack *b, t_node *node, t_cost *c);
void	calculate_four_costs(t_stack *a, t_stack *b, t_cost *c, int costs[4]);
int	find_best_case(int costs[4]);
int	get_node_index(t_stack *stack, t_node *target);
void	set_case_three_cost(t_cost *c, int ra_cost, int rrb_cost, int total);
void	set_case_four_cost(t_cost *c, int rra_cost, int rb_cost, int total);

// exec_case_ab.c
void	execute_case_one(t_stack *a, t_stack *b, t_cost *c, char *push_op);
void	execute_case_two(t_stack *a, t_stack *b, t_cost *c, char *push_op);
void	execute_case_three(t_stack *a, t_stack *b, t_cost *c, char *push_op);
void	execute_case_four(t_stack *a, t_stack *b, t_cost *c, char *push_op);

// helper.c
t_node	*get_node_at(t_stack *stack, int index);
int	find_place_in_b(t_stack *b, int value);
int	get_index_of_min(t_stack *b);
int	get_index_of_max(t_stack *s);
int	find_place_in_a(t_stack *a, int value);
int	get_index_between_b(t_stack *b, int value);
int	get_index_between_a(t_stack *a, int value);

#endif