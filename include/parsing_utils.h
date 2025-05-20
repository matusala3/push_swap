#ifndef PARSING_UTILS_H
#define PARSING_UTILS_H

#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

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

bool safe_atoi(const char *str, int *out);

#endif