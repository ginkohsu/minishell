/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:39:39 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/30 13:28:28 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"

/*
** Complex test case with builtin and external commands
** Simulates: echo "hello" | cat > output.txt
*/
t_ast	*create_test_ast(void)
{
	t_ast	*pipe_ast;
	t_ast	*left;
	t_ast	*right;
	t_redir	*redir;

	right = malloc(sizeof(t_ast));
	right->type = CMD;
	right->cmd.argv = malloc(2 * sizeof(char *));
	right->cmd.argv[0] = ft_strdup("cat");
	right->cmd.argv[1] = NULL;
	redir = malloc(sizeof(t_redir));
	redir->type = REDIR_OUT;
	redir->filename = ft_strdup("output.txt");
	redir->next = NULL;
	right->cmd.redirs = redir;
	left = malloc(sizeof(t_ast));
	left->type = CMD;
	left->cmd.argv = malloc(3 * sizeof(char *));
	left->cmd.argv[0] = ft_strdup("echo");
	left->cmd.argv[1] = ft_strdup("hello");
	left->cmd.argv[2] = NULL;
	left->cmd.redirs = NULL;
	pipe_ast = malloc(sizeof(t_ast));
	pipe_ast->type = PIPE;
	pipe_ast->s_pipe.left = left;
	pipe_ast->s_pipe.right = right;
	return (pipe_ast);
}

// recursive ast command counter
int	count_ast_commands(t_ast *ast)
{
	if (!ast)
		return (0);
	if (ast->type == CMD)
		return (1);
	return (count_ast_commands(ast->s_pipe.left)
		+ count_ast_commands(ast->s_pipe.right));
}

void	free_ast(t_ast *ast)
{
	t_redir	*redir;
	t_redir	*next;
	int		i;

	if (!ast)
		return ;
	if (ast->type == CMD)
	{
		i = 0;
		if (ast->cmd.argv)
		{
			while (ast->cmd.argv[i])
			{
				free(ast->cmd.argv[i]);
				i++;
			}
			free(ast->cmd.argv);
		}
		redir = ast->cmd.redirs;
		while (redir)
		{
			next = redir->next;
			free(redir->filename);
			free(redir);
			redir = next;
		}
	}
	else
	{
		free_ast(ast->s_pipe.left);
		free_ast(ast->s_pipe.right);
	}
	free(ast);
}
