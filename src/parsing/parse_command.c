/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:19:09 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/04 20:53:11 by jinxu            ###   ########.fr       */
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

char	*merge_adjacent_tokens(t_parser *parser, char *current_arg,
		t_token *current_token)
{
	t_token	*next_token;
	char	*next_arg;
	char	*merged;

	next_token = parser_peek(parser, 0);
	while (next_token && is_string_token(next_token)
		&& current_token->no_space_after)
	{
		next_arg = expand_token_value_basic(next_token);
		if (!next_arg)
			next_arg = ft_strdup("");
		merged = ft_strjoin_safe(current_arg, next_arg);
		free(current_arg);
		free(next_arg);
		if (!merged)
			return (NULL);
		current_arg = merged;
		parser_consume(parser);
		current_token = next_token;
		next_token = parser_peek(parser, 0);
	}
	return (current_arg);
}

static int	process_argument_token(t_parser *parser, t_ast *cmd_node)
{
	t_token	*token;
	char	*arg;

	token = parser_peek(parser, 0);
	if (!token || !is_string_token(token))
		return (0);
	arg = expand_token_value_basic(token);
	if (!arg)
		arg = ft_strdup("");
	parser_consume(parser);
	if (arg && *arg == '\0')
	{
		free(arg);
		return (1);
	}
	arg = merge_adjacent_tokens(parser, arg, token);
	if (!arg)
	{
		free_ast(cmd_node);
		return (0);
	}
	return (add_argument_to_cmd(&cmd_node->cmd, arg) == PARSE_SUCCESS);
}

static int	process_current_token(t_parser *parser, t_ast *cmd_node,
		t_token *token)
{
	if (is_redirection_token(token))
		return (process_redirection_token(parser, cmd_node));
	else if (is_string_token(token))
		return (process_argument_token(parser, cmd_node));
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
//		printf("syntax error: empty command\n");
		free_ast(cmd_node);
		return (NULL);
	}
	return (cmd_node);
}
