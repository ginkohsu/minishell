NAME := minishell
SRC := main.c free.c handle_env.c handle_quote.c handle_redir.c handle_word.c lexer.c utils.c
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
