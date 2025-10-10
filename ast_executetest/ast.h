/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:15:02 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/30 13:41:20 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../libft/include/libft.h"

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}							t_redir_type;

typedef struct s_redir
{
	t_redir_type			type;
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
		} pipe;
	};
}							t_ast;

t_ast						*create_test_ast(void);
void	execute_ast(t_ast *ast); // Amit's execute part?
void						free_ast(t_ast *ast);

#endif
