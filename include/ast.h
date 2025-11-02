/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:15:02 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/02 23:16:15 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../libft/include/libft.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND, // >>
	TOKEN_HEREDOC,      // <<
	TOKEN_SQUOTE,       // ''
	TOKEN_DQUOTE,       // ""
	TOKEN_ENV_VAR,      //$HOME
	TOKEN_EXIT_STATUS,  //$?
	TOKEN_EOF           //?
}							t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	int						no_space_after;
}							t_token;

typedef struct s_parser
{
	t_token					*tokens;
	int						token_count;
	int						current_pos;
}							t_parser;

typedef enum e_parse_status
{
	PARSE_SUCCESS,
	PARSE_SYNTAX_ERROR,
	PARSE_MALLOC_ERROR
}							t_parse_status;

typedef struct s_redir
{
	t_token_type			type;
	char					*filename;
	struct s_redir			*next;
}							t_redir;

typedef struct s_command
{
	char					**argv;
	t_redir					*redirs;
}							t_command;

typedef enum e_node_type
{
	CMD,
	PIPE
}							t_node_type;

typedef struct s_ast
{
	t_node_type				type;
	union
	{
		t_command			cmd;
		struct
		{
			struct s_ast	*left;
			struct s_ast	*right;
		} s_pipe;
	};
}							t_ast;

t_ast						*create_test_ast(void);
void						free_ast(t_ast *ast);

#endif
