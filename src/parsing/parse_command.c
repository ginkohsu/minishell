/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:19:09 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/26 21:18:51 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_redirection_token(t_parser *parser, t_ast *cmd_node)
{
	int	status;

	status = parse_redirection(parser, &cmd_node->cmd);
	if (status != PARSE_SUCCESS)
	{
		free_ast(cmd_node);
		return (0);
	}
	return (1);
}

static int	process_string_token(t_parser *parser, t_ast *cmd_node)
{
	t_token	*token;
	char	*expanded;
	int		status;

	token = parser_peek(parser, 0);
	if (!token)
		return (0);
	expanded = expand_token_value_basic(token);
	if (!expanded)
	{
		free_ast(cmd_node);
		return (0);
	}
	parser_consume(parser);
	status = add_argument_to_cmd(&cmd_node->cmd, expanded);
	if (status != PARSE_SUCCESS)
	{
		free(expanded);
		free_ast(cmd_node);
		return (0);
	}
	return (1);
}

static int	process_current_token(t_parser *parser, t_ast *cmd_node,
		t_token *token)
{
	if (is_redirection_token(token))
		return (process_redirection_token(parser, cmd_node));
	else if (is_string_token(token))
		return (process_string_token(parser, cmd_node));
	parser_consume(parser);
	return (1);
}

t_ast	*parse_command(t_parser *parser)
{
	t_ast	*cmd_node;
	t_token	*token;

	cmd_node = create_command_node();
	if (!cmd_node)
		return (NULL);
	token = parser_peek(parser, 0);
	while (token && !is_terminating_token(token))
	{
		if (!process_current_token(parser, cmd_node, token))
			return (NULL);
		token = parser_peek(parser, 0);
	}
	if ((!cmd_node->cmd.argv || !cmd_node->cmd.argv[0])
		&& !cmd_node->cmd.redirs)
	{
		printf("syntax error: empty command\n");
		free_ast(cmd_node);
		return (NULL);
	}
	return (cmd_node);
}
