/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:29:58 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/26 17:13:17 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../get_next_line/get_next_line.h"
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

// parsing functions
void	free_stack(t_stack *stack);
void	free_split_arg(char **split);
bool	safe_atoi(const char *str, int *out);
bool	stack_append(t_stack *stack_a, int val);
bool	parse_input(char **argv, t_stack *stack_a);
bool	process_argv_entry(char **splitted_arg, t_stack *stack_a);

// checking duplication
bool	check_duplicates(t_stack *stack_a);
void	insertion_sort(int *arr, int size);
int		*copy_stack_to_array(t_stack stack_a, int size);
void	heap_sort(int *arr, int size);
void	heapify(int *arr, int size, int root);
void	swap_int(int *a, int *b);

// operations
void	swap_stack(t_stack *stack);
void	rotate(t_stack *stack);
void	reverse_rotate(t_stack *stack);
void	pusha_to_b(t_stack *stack_a, t_stack *stack_b);
void	pushb_to_a(t_stack *stack_a, t_stack *stack_b);
int		execute_instruction_silent(t_stack *a, t_stack *b, char *op);
void	swap_both(t_stack *a, t_stack *b);
void	rotate_both(t_stack *a, t_stack *b);
void	reverse_rotate_both(t_stack *a, t_stack *b);
int		ft_strcmp(char *s1, char *s2);
void	trim_newline(char *str);

// checking if sorted
bool	is_sorted(t_stack *stack);

#endif