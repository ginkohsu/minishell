NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/main.c

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -lreadline

clean:
	rm -f

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

