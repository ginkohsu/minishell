/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:15:02 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/10 13:13:19 by jinxu            ###   ########.fr       */
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

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
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

t_ast	*parse(char *input);
void	execute_ast(t_ast *ast);//Amit's execute part?
void	free_ast(t_ast *ast);

#endif
