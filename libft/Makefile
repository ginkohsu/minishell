NAME = libft.a

# Source files organized by category
STOCK_SRC = ft_strlen.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c \
			ft_strlcat.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
			ft_split.c ft_strmapi.c ft_striteri.c ft_atoi.c ft_itoa.c \
			ft_calloc.c ft_bzero.c ft_memset.c ft_memcpy.c ft_memmove.c \
			ft_strnstr.c

STR_TOOLS_SRC = ft_strapp.c ft_strprep.c ft_strndup.c \
				ft_atol.c ft_atoll.c ft_atod.c ft_itoa_base.c

ARR_TOOLS_SRC = arrlen.c arrlcpy.c arrdup.c arrndup.c arrstr.c arrstrn.c \
				arrsort.c free_array.c

CURSUS_SRC = get_next_line.c ft_printf.c ft_fprintf.c

MINISHELL_SRC = ft_strcmp.c ft_putnbr_fd.c ft_strjoin_safe.c ft_strlen_z.c \
				print_char.c print_hex.c print_nbr.c print_ptr.c \
				print_str.c print_unsignedint.c ft_isalpha.c ft_isalnum.c \
				ft_isascii.c ft_isprint.c ft_isdigit.c

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Add directory prefixes
STOCK = $(addprefix $(SRC_DIR)/stock/,$(STOCK_SRC))
STR_TOOLS = $(addprefix $(SRC_DIR)/str_tools/,$(STR_TOOLS_SRC))
ARR_TOOLS = $(addprefix $(SRC_DIR)/arr_tools/,$(ARR_TOOLS_SRC))
CURSUS = $(addprefix $(SRC_DIR)/cursus/,$(CURSUS_SRC))
MINISHELL = $(addprefix $(SRC_DIR)/minishell/,$(MINISHELL_SRC))

SRC = $(STOCK) $(STR_TOOLS) $(ARR_TOOLS) $(CURSUS) $(MINISHELL)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Compilation flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -I$(INC_DIR)

# Rules
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
