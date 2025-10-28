/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:55:04 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/29 00:13:12 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int g_exit_status; //for exit status

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define MAX_TOKENS 1000

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

typedef struct	s_parser
{
	t_token	*tokens;
	int		token_count;
	int		current_pos;
}	t_parser;

typedef enum	e_parse_status
{
	PARSE_SUCCESS,
	PARSE_SYNTAX_ERROR,
	PARSE_MALLOC_ERROR
}	t_parse_status;

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char		**argv;
	t_redir		*redirs;
}	t_command;

typedef enum e_node_type
{
	CMD,
	PIPE
}	t_node_type;

typedef struct s_ast
{
	t_node_type	type;
	union
	{
		t_command	cmd;
		struct
		{
			struct s_ast	*left;
			struct s_ast	*right;
		}	pipe;
	};
}	t_ast;

//tokenizing
int				ft_isspace(char c);
int				is_only_whitespace(char *str);
void			skip_whitespace(char **input);

int				is_special_char(char c);
char			*extract_word(char **input);
int				check_unclosed_quote(char *input);
void			handle_quote_char(char **input, 
				t_token *collected_tokens, int *count);
void			handle_redirect_char(char **input, 
				t_token *collected_tokens, int *count);
void			handle_single_special_char(char **input,
				t_token *collected_tokens, int *count);
void			handle_env_var_char(char **input, 
				t_token *collected_tokens, int *count);
char    		*handle_env_var(char **input);

t_token			*tokenize(char *input, int *token_count);

void			cleanup_stack_tokens(t_token *tokens, int count);
void			free_tokens(t_token *tokens, int count);

//parsing
t_parser		parser_init(t_token *tokens, int count);
t_token			*parser_peek(t_parser *parser, int offset);
t_token			*parser_consume(t_parser *parser);
int				parser_check(t_parser *parser, t_token_type type);
int				is_redirection_token(t_token *token);
int				is_terminating_token(t_token *token);
int				is_string_token(t_token *token);
t_ast			*create_command_node(void);
t_ast			*create_pipe_node(t_ast *left, t_ast *right);
char			*expand_simple_env_var(char *var_name);
char			*expand_token_value_basic(t_token *token);
char			*expand_vars_dquote(char *src);

t_ast			*parse_pipeline(t_parser *parser);
t_ast			*parse_command(t_parser *parser);
int				add_argument_to_cmd(t_command *cmd, char *arg);
int				parse_redirection(t_parser *parser, t_command *cmd);
t_ast			*parse(char *input);
void			execute_ast(t_ast *ast);//Amit's execute part?
void			free_ast(t_ast *ast);


//for testing:
void			print_ast(t_ast *ast, int depth);
void			print_tokens_debug(t_token *tokens, int count);
const char		*get_token_type_name(t_token_type type);
const char		*get_node_type_name(t_node_type type);
#endif
