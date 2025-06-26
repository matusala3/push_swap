/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:35:17 by magebreh          #+#    #+#             */
/*   Updated: 2025/06/26 16:59:02 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/checker_bonus.h"

int main(int argc, char **argv)
{
   t_stack stack_a;
   t_stack stack_b;
   char    *line;

   if (argc < 2)
       return (0);
   stack_a =(t_stack) {NULL, NULL, 0};
   stack_b =(t_stack) {NULL, NULL, 0};
   if (!parse_input(argv, &stack_a))
   {
       write(2, "Error\n", 6);
       free_stack(&stack_a);
       return (1);
   }
   if (check_duplicates(&stack_a))
   {
       write(2, "Error\n", 6);
       free_stack(&stack_a);
       return (1);
   }
   while ((line = get_next_line(0)) != NULL)
   {
       if (!execute_instruction_silent(&stack_a, &stack_b, line))
       {
           write(2, "Error\n", 6);
           free(line);
           free_stack(&stack_a);
           free_stack(&stack_b);
           return (1);
       }
       free(line);
   }
   if (is_sorted(&stack_a) && stack_b.size == 0)
       write(1, "OK\n", 3);
   else
       write(1, "KO\n", 3);
   free_stack(&stack_a);
   free_stack(&stack_b);
   return (0);
}