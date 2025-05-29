/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:31:19 by magebreh          #+#    #+#             */
/*   Updated: 2025/05/29 14:31:37 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	execute_instruction(t_stack *a, t_stack *b, char *op)
{
	if (!ft_strcmp(op, "sa"))
		swap_stack(a);
	else if (!ft_strcmp(op, "sb"))
		swap_stack(b);
	else if (!ft_strcmp(op, "ss"))
		swap_stack(a), swap_stack(b);
	else if (!ft_strcmp(op, "pa"))
		pushb_to_a(a, b);
	else if (!ft_strcmp(op, "pb"))
		pusha_to_b(a, b);
	else if (!ft_strcmp(op, "ra"))
		rotate(a);
	else if (!ft_strcmp(op, "rb"))
		rotate(b);
	else if (!ft_strcmp(op, "rr"))
		rotate(a), rotate(b);
	else if (!ft_strcmp(op, "rra"))
		reverse_rotate(a);
	else if (!ft_strcmp(op, "rrb"))
		reverse_rotate(b);
	else if (!ft_strcmp(op, "rrr"))
		reverse_rotate(a), reverse_rotate(b);
	if(write(1, op, ft_strlen(op)) || write(1, "\n", 1))
		return (-1);
}

