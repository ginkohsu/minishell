# Execution test Makefile
# Switch between tests:
#   make simple    - Build simple test (no redirections)
#   make full      - Build full test (with redirections)

NAME		:= ast_test
NAME_SIMPLE	:= ast_simple
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
LIBFT_DIR	:= ../libft
LIBFT		:= $(LIBFT_DIR)/libft.a
INC			:= -I. -I$(LIBFT_DIR)/include

# Core source files (shared)
CORE_SRCS	:= execution.c \
			   children.c \
			   command_exec.c \
			   builtins.c \
			   builtins2.c \
			   environment.c \
			   exec_tools.c \
			   redirs.c \
			   debug.c

# Full test (original with redirections)
FULL_SRCS	:= test_main.c \
			   test_ast.c \
			   $(CORE_SRCS)

# Simple test (no redirections)
SIMPLE_SRCS	:= test_simple.c \
			   test_ast.c \
			   $(CORE_SRCS)

SRCS		:= $(SIMPLE_SRCS)

OBJS		:= $(SRCS:.c=.o)
FULL_OBJS	:= $(FULL_SRCS:.c=.o)
SIMPLE_OBJS	:= $(SIMPLE_SRCS:.c=.o)

all: simple

simple: SRCS = $(SIMPLE_SRCS)
simple: NAME = $(NAME_SIMPLE)
simple: $(NAME_SIMPLE)

full: SRCS = $(FULL_SRCS)
full: NAME = $(NAME)
full: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(FULL_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(FULL_OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "✓ Built $(NAME) successfully"

$(NAME_SIMPLE): $(SIMPLE_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SIMPLE_OBJS) -L$(LIBFT_DIR) -lft -o $(NAME_SIMPLE)
	@echo "✓ Built $(NAME_SIMPLE) successfully"

%.o: %.c ast.h execution.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(FULL_OBJS) $(SIMPLE_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_SIMPLE)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all simple full clean fclean re
