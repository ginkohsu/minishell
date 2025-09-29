NAME = libft.a
SRC =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strcmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c	\
		ft_calloc.c \
		ft_strdup.c \
		ft_strndup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putint_fd.c \
		ft_putuint_fd.c \
		get_next_line.c \
		ft_printf.c \
		ft_fprintf.c \
		ft_strapp.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_strlen_z.c ft_strjoin_safe.c get_next_line.c \
		print_ptr.c print_str.c print_unsignedint.c

SRC_DIR := src
OBJ_DIR := obj

OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
INC := -I./include
CFLAGS := -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)
	$(MAKE) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean: $(OBJ_DIR)
	rm -r $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all
