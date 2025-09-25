/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:55:04 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/23 15:55:01 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

# define MAX_TOKENS 100

typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,// >>
	TOKEN_HEREDOC,// <<
	TOKEN_SQUOTE,// ''
	TOKEN_DQUOTE,// ""
	TOKEN_EOF //?
} t_token_type;

typedef struct s_token {
	t_token_type type;
	char *value;
} t_token;

int				ft_isspace(char c);
int				is_special_char(char c);
t_token_type    get_token_type(char c);

t_token			*tokenize(char *input, int *token_count);

void			free_tokens(t_token *tokens, int count);

//for testing:
void		print_tokens_debug(t_token *tokens, int count);

#endif
