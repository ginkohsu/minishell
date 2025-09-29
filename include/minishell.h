/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:55:04 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/27 02:07:00 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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
	TOKEN_ENV_VAR, //$HOME
	TOKEN_EXIT_STATUS, //$?
	TOKEN_EOF //?
} t_token_type;

typedef struct s_token {
	t_token_type type;
	char *value;
} t_token;

void			skip_whitespace(char **input);
int				ft_isspace(char c);
int				is_special_char(char c);
char			*extract_word(char **input);
void			handle_quote_char(char **input, 
				t_token *collected_tokens, int *count);
void			handle_redirect_char(char **input, 
				t_token *collected_tokens, int *count);
void			handle_single_special_char(char **input,
				t_token *collected_tokens, int *count);
void			handle_env_var_char(char **input, 
				t_token *collected_tokens, int *count);

t_token			*tokenize(char *input, int *token_count);

void			free_tokens(t_token *tokens, int count);

//for testing:
void		print_tokens_debug(t_token *tokens, int count);
#endif
