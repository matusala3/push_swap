#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

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

#endif  
