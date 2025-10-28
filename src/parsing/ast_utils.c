/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:31:41 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/26 21:17:09 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_command_node(void)
{
	t_ast	*ast;
	
	ast = malloc(sizeof(t_ast));
	if (!ast)
	{
		perror("malloc failed in create_command_node");
		return (NULL);
	}
	ast->type = CMD;
	ast->cmd.argv = NULL;
	ast->cmd.redirs = NULL;

	return (ast);
}

t_ast	*create_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->type = PIPE;
	ast->s_pipe.left = left;
	ast->s_pipe.right = right;
	return (ast);
}
