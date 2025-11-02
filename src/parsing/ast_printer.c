/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:32:03 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/02 17:32:05 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*get_redir_type_name(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return ("<");
	if (type == TOKEN_REDIR_OUT)
		return (">");
	if (type == TOKEN_REDIR_APPEND)
		return (">>");
	if (type == TOKEN_HEREDOC)
		return ("<<");
	return ("UNKNOWN");
}

const char	*get_node_type_name(t_node_type type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == CMD)
		return ("COMMAND");
	return ("UNKNOWN");
}

static void	print_redirections(t_redir *redirs, int depth)
{
	t_redir	*current;

	current = redirs;
	while (current)
	{
		printf("%*sREDIR: %s %s\n", depth * 2, "",
			get_redir_type_name(current->type), current->filename);
		current = current->next;
	}
}

static void	print_command(t_command *cmd, int depth)
{
	int	i;

	printf("%*sARGUMENTS: ", depth * 2, "");
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			printf("[%s] ", cmd->argv[i]);
			i++;
		}
	}
	printf("\n");
	if (cmd->redirs)
		print_redirections(cmd->redirs, depth + 1);
}

void	print_ast(t_ast *ast, int depth)
{
	if (!ast)
		return ;
	if (ast->type == CMD)
	{
		printf("%*s%s\n", depth * 2, "", get_node_type_name(ast->type));
		print_command(&ast->cmd, depth + 1);
	}
	else if (ast->type == PIPE)
	{
		printf("%*s%s\n", depth * 2, "", get_node_type_name(ast->type));
		printf("%*sLEFT:\n", (depth + 1) * 2, "");
		print_ast(ast->s_pipe.left, depth + 2);
		printf("%*sRIGHT:\n", (depth + 1) * 2, "");
		print_ast(ast->s_pipe.right, depth + 2);
	}
}
