/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:59:13 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/26 21:19:05 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redir(t_redir *redir)
{
	t_redir	*next;
	
	while (redir)
	{
		next = redir->next;
		free(redir->filename);
		free(redir);
		redir = next;
	}
}

static void	free_command(t_command *cmd)
{
	int	i;
	
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	free_redir(cmd->redirs);
}

void	free_ast(t_ast	*ast)
{
	if (!ast)
		return ;
	if (ast->type == CMD)
		free_command(&ast->cmd);
	else
	{
		free_ast(ast->pipe.left);
		free_ast(ast->pipe.right);
	}
	free(ast);
}
