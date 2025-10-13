/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:31:41 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/13 15:04:43 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	*create_command_node(void)
{
	t_ast	*ast;
	
	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL); //error handling??????

	ast->type = NODE_CMD;
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
	ast->type = NODE_PIPE;
	ast->pipe.left = left;
	ast->pipe.right = right;
	return (ast);
}
