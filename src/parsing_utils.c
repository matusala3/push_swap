#include "push_swap.h"

bool safe_atoi(const char *str, int *out)
{
	int	i = 0;
	int	sign = 1;
	int	result = 0;

	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return false;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (INT_MAX - (str[i] - '0')) / 10)
			return false;
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return false;
	*out = result * sign;
	return true;
}

void free_split_arg(char **split) 
{
    int i = 0;

    while (split[i])
        free(split[i++]);
    free(split);
}

bool stack_append(t_stack *stack_a, int val)
{
	t_node	*node;
	node = malloc(sizeof(t_node));
	if (!node)
		return (false);
	node->value = val;
	node->next = NULL;
	node->prev = NULL;	
	if(stack_a->head == NULL)
	{
		stack_a->head = node;
		stack_a->tail = node;
	}
	else
	{
		node->prev = stack_a->tail;
		stack_a->tail->next = node;
		stack_a->tail = node;
	}
	stack_a->size++;
	return (true);
}

void free_stack(t_stack *stack)
{
	t_node *current;

	current = stack-> head;
	while (current)
	{
		t_node *next = current->next;
		free(current);
		current = next;
	}
	stack->head = NULL;
	stack->tail = NULL;
	stack->size = 0;
}
bool process_argv_entry(char **splitted_arg, t_stack *stack_a)
{
	int i;
	int val;
	bool res;

	i = 0;
	while(splitted_arg[i])
	{
		if (!safe_atoi(splitted_arg[i], &val))
		{
			free_split_arg(splitted_arg);
			return false;
		}
		i++;
		res = stack_append(stack_a, val);
		if (!res)
		{
			free_split_arg(splitted_arg);
			free_stack(stack_a);
			return false;
		}
	}
	return (true);
}

bool parse_input(char **argv, t_stack *stack_a)
{
	int i;
	bool res;
    char **splitted_arg;

    i = 1;
    while (argv[i])
    {
        splitted_arg = ft_split(argv[i], ' ');
        res = process_argv_entry(splitted_arg, stack_a);
		free_split_arg(splitted_arg);
		if (!res)
		{
			free_split_arg(splitted_arg);
			free_stack(stack_a);
			return false;
		}
		i++;
    }
    return true;
}
