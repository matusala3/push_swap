#include "../include/push_swap.h"
#include "../include/parsing_utils.h"
#include "../libft/libft.h"

int main(int argc, char **argv)
{
    int i;
    int j;
    int k;
    int num;
    bool res;
    char **splitted_arg;

    i = 1;
    if (argc == 1)
        return 0;
	printf("Program started with %d arguments:\n", argc - 1);
    while(argv[i])
    {
		printf("\nProcessing argument %d: '%s'\n", i, argv[i]);
           splitted_arg = ft_split(argv[i], ' ');
           if(!splitted_arg)
           {
                write(2, "Error\n", 6);
                return (1);
            }
            j = 0;
            while(splitted_arg[j])
            {
				printf("  Checking token %d: '%s'\n", j, splitted_arg[j]);
                res = safe_atoi(splitted_arg[j], &num);
                if(!res)
                {
                    k = 0;
                    while (splitted_arg[k])
                        free(splitted_arg[k++]);
                    free(splitted_arg);
                    write(2, "Error\n", 6);
                    return (1);
                }
				printf("  Valid number: %d\n", num);
                j++;
            }
            i++;
		}
}
