# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 01:14:35 by magebreh          #+#    #+#              #
#    Updated: 2025/06/26 17:10:31 by magebreh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
BONUS_NAME = checker
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
AR = ar rcs
RM = rm -f
SRC = src/check_duplicate.c \
	  src/check_duplicate_utils.c \
	  src/mechanical_turk.c \
	  src/moves.c \
	  src/parsing_utils.c \
	  src/push_swap.c \
	  src/cost_calculation.c \
	  src/exec_case.c \
	  src/set_cases.c \
	  src/helper.c \
	  src/small_sort.c \
	  src/stack_op.c \

BONUS_SRC = bonus/checker_bonus.c \
			bonus/checker_parsing.c \
			bonus/checker_duplicates.c \
			bonus/checker_operations.c \
			bonus/checker_moves.c \

GNL_SRC = get_next_line/get_next_line.c \
		  get_next_line/get_next_line_utils.c

OBJ_DIR = obj

OBJ := $(SRC:src/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ := $(BONUS_SRC:bonus/%.c=$(OBJ_DIR)/%.o) $(GNL_SRC:get_next_line/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS_NAME)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "Libft compiled."

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: bonus/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: get_next_line/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "Executable $(NAME) created."

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(BONUS_OBJ) -L$(LIBFT_DIR) -lft -o $(BONUS_NAME)
	@echo "Executable $(BONUS_NAME) created."

clean:
	@$(RM) $(OBJ) $(BONUS_OBJ)	
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "Object files cleaned."

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "All files cleaned."

re: fclean all

.PHONY: all clean fclean re