#include "../include/push_swap.h"
#include "../include/parsing_utils.h"
#include "../libft/libft.h"


int main(int argc, char **argv)
{
    int i;
    int total_num;

	i = 1;
    total_num = 0;
	if (argc == 1)
		return 0;
	printf("Program started with %d arguments:\n", argc - 1);
    if (!parse_and_count(argv + 1, &total_num))
    {
        write(2, "Error\n", 6);
        return 1;
    }
    printf("Total number of numbers %i", total_num);
}
