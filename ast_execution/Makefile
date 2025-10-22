# AST Execution - Test Suite

NAME		:= test
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
LIBFT_DIR	:= ../libft
LIBFT		:= $(LIBFT_DIR)/libft.a
INC			:= -I. -I$(LIBFT_DIR)/include

# Source files
SRCS		:= tests/test.c \
			   exec_ast.c \
			   children.c \
			   exec_cmd.c \
			   builtins.c \
			   builtins_more.c \
			   environment.c \
			   exec_utils.c \
			   exittool.c \
			   redirection.c \
			   array_utils.c

OBJS		:= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "✓ Built $(NAME) successfully"

%.o: %.c ast.h execution.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
