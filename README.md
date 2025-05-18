push_swap/
├── Makefile
├── README.md

├── include/
│   ├── push_swap.h                # Main program types and strategy selector prototypes
│   ├── parsing_utils.h            # Input parsing and validation prototypes
│   ├── stack_utils.h              # Stack operations prototypes (push, pop, swap, rotate, etc.)
│   ├── small_sort.h               # Small sort (2-5 elements) prototypes
│   ├── mechanical_turk.h          # Mechanical Turk strategy (6-500 elements) prototypes
│   ├── radix_sort.h               # Radix sort (500+ elements) prototypes
│   ├── cost_utils.h               # Move cost calculation prototypes (for Mechanical Turk)

├── src/
│   ├── push_swap.c                # Main entry point and strategy selector
│   ├── parsing_utils.c            # Input parsing and validation
│
│   ├── stack_basic_ops.c          # push, pop, swap
│   ├── stack_rotation_ops.c       # rotate, reverse rotate, stack_size, is_sorted
│
│   ├── small_sort.c               # Small size handling logic (2-5 elements)
│   ├── mechanical_turk.c          # Mechanical Turk cost-based logic (6-500 elements)
│   ├── radix_sort.c               # Radix sort logic (500+ elements)
│
│   ├── move_utils.c               # Helpers for performing combined moves (rr, rrr)
│   └── cost_utils.c               # Cost calculation functions for Mechanical Turk

└── libft/
    ├── Makefile
    ├── *.c
    └── *.h
# push_swap
# push_swap
