NAME := minishell
SRC := ast_utils.c     handle_redir.c  parse_command.c   parser_otherutils.c \
expand_utils.c  handle_word.c   parse_free.c      parser_utils.c \
free.c          lexer.c         parse_main.c      utils.c \
handle_env.c    main.c          parse_pipeline.c \
handle_quote.c  parse_args.c    parse_redir.c \
expand_vars_dquote.c ast_printer.c 
SRC_DIR := src
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

HEADER := include/$(NAME).h
OBJ_DIR := obj
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
INC := -I./include -I./libft/include

CFLAGS := -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

all: $(NAME)

bonus: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) $(OBJ) -L./$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	cc $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f compile_commands.json
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
