/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:15:02 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/18 01:10:11 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef AST_H
# define AST_H

#include "minishell.h"

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

t_parser	parser_init(t_token *tokens, int count);
t_token		*parser_peek(t_parser *parser, int offset);
t_token		*parser_consume(t_parser *parser);
int			parser_check(t_parser *parser, t_token_type type);
int			is_redirection_token(t_token *token);
int			is_terminating_token(t_token *token);
int			is_string_token(t_token *token);
t_ast		*create_command_node(void);
t_ast		*create_pipe_node(t_ast *left, t_ast *right);
char		*expand_simple_env_var(char *var_name);
char		*expand_token_value_basic(t_token *token);

t_ast		*parse_pipeline(t_parser *parser);
t_ast		*parse_command(t_parser *parser);
int			add_argument_to_cmd(t_command *cmd, char *arg);
int			parse_redirection(t_parser *parser, t_command *cmd);
t_ast		*parse(char *input);
void		execute_ast(t_ast *ast);//Amit's execute part?
void		free_ast(t_ast *ast);

#endif
