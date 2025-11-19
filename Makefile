NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
INC := -I./include -I./libft/include -I.
OBJ_DIR := obj

SRCS := main.c ast_utils.c expand_utils.c expand_vars_dquote.c \
	free.c handle_env.c handle_quote.c handle_redir.c handle_word.c \
	lexer.c parse_args.c parse_command.c parse_free.c parse_main.c \
	parse_pipeline.c parse_redir.c parser_otherutils.c parser_utils.c utils.c \
	parse_heredoc.c builtins.c builtins_more.c children.c \
	environment.c exec_ast.c exec_cmd.c exec_utils.c exittool.c \
	heredoc.c heredoc_utils.c redirection.c signal.c

OBJS := $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

VPATH := src:src/parsing:src/execution

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: %.c include/ast.h include/execution.h include/minishell.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
