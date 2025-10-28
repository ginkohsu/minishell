/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:53:48 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/26 21:19:40 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int create_add_redir(t_token_type type, char *filename, t_command *cmd)
{
	t_redir	*redir;
	t_redir	*last;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->type = type;
	redir->filename = filename;
	redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
	return (1);
}

static int	validate_redir_syntax(t_parser *parser)
{
	t_token	*redir_token;
	t_token *filename_token;

	redir_token = parser_peek(parser, 0);
	if (!redir_token || !is_redirection_token(redir_token))
		return (0);
	parser_consume(parser);	
	filename_token = parser_peek(parser, 0);
	if (!filename_token || !is_string_token(filename_token))
		return (0);
	return (1);
}
static int	process_redir_tokens(t_parser *parser, char **filename)
{
	*filename = expand_token_value_basic(parser_peek(parser, 0));
	if (!*filename)
		return (0);
	parser_consume(parser);
	return (1);
}

int	parse_redirection(t_parser *parser, t_command *cmd)
{
	t_token	*redir_token;
	char	*filename;
	
	if (!validate_redir_syntax(parser))
		return (PARSE_SYNTAX_ERROR);
	redir_token = parser_peek(parser, -1);
	if (!process_redir_tokens(parser, &filename))
	{
		free(filename);
		return (PARSE_MALLOC_ERROR);
	}
	if (!create_add_redir(redir_token->type, filename, cmd))
	{
		free(filename);
		return (PARSE_MALLOC_ERROR);
	}
	return (PARSE_SUCCESS);
}
