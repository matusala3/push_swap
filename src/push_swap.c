#include "../include/push_swap.h"
#include "../include/parsing_utils.h"


int main(int argc, char **argv)
{
    t_stack stack_a;

    stack_a.head = NULL;
    stack_a.tail = NULL;
    stack_a.size = 0;
	if (argc == 1)
		return 0;
	printf("Program started with %d arguments:\n", argc - 1);
    if (!parse_input(argv, &stack_a))
    {
        write(2, "Error\n", 6);
        return 1;
    }
    free_stack(&stack_a);
    return 0;
}
