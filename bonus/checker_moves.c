/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:00:00 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/26 17:13:05 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/checker_bonus.h"

void	trim_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

int	execute_instruction_silent(t_stack *a, t_stack *b, char *op)
{
	trim_newline(op);
	if (!ft_strcmp(op, "sa"))
		swap_stack(a);
	else if (!ft_strcmp(op, "sb"))
		swap_stack(b);
	else if (!ft_strcmp(op, "ss"))
		swap_both(a, b);
	else if (!ft_strcmp(op, "pa"))
		pushb_to_a(a, b);
	else if (!ft_strcmp(op, "pb"))
		pusha_to_b(a, b);
	else if (!ft_strcmp(op, "ra"))
		rotate(a);
	else if (!ft_strcmp(op, "rb"))
		rotate(b);
	else if (!ft_strcmp(op, "rr"))
		rotate_both(a, b);
	else if (!ft_strcmp(op, "rra"))
		reverse_rotate(a);
	else if (!ft_strcmp(op, "rrb"))
		reverse_rotate(b);
	else if (!ft_strcmp(op, "rrr"))
		reverse_rotate_both(a, b);
	else
		return (0);
	return (1);
}

void	swap_both(t_stack *a, t_stack *b)
{
	swap_stack(a);
	swap_stack(b);
}

void	rotate_both(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
}

void	reverse_rotate_both(t_stack *a, t_stack *b)
{
	reverse_rotate(a);
	reverse_rotate(b);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	return (s1[i] - s2[i]);
}

bool	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (stack->size < 2)
		return (true);
	current = stack->head;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (false);
		current = current->next;
	}
	return (true);
} 