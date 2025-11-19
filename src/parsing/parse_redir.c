/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:53:48 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/18 22:49:21 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_redir(t_token_type type, char *filename, t_command *cmd,
		int quoted)
{
	t_redir	*redir;
	t_redir	*last;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->type = type;
	redir->filename = filename;
	redir->next = NULL;
	redir->quoted = quoted;
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
	t_token	*filename_token;

	redir_token = parser_peek(parser, 0);
	if (!redir_token || !is_redirection_token(redir_token))
		return (0);
	filename_token = parser_peek(parser, 1);
	if (!filename_token || !is_string_token(filename_token))
		return (0);
	parser_consume(parser);
	return (1);
}

static void	check_heredoc_quotes(t_parser *parser, t_token *token, int *quoted)
{
	t_token	*next;
	int		offset;

	if (token->type == TOKEN_DQUOTE || token->type == TOKEN_SQUOTE)
		*quoted = 1;
	offset = 1;
	next = parser_peek(parser, offset);
	while (next && is_string_token(next) && token->no_space_after)
	{
		if (next->type == TOKEN_DQUOTE || next->type == TOKEN_SQUOTE)
			*quoted = 1;
		token = next;
		offset++;
		next = parser_peek(parser, offset);
	}
}

static char	*handle_heredoc_filename(t_token *filename_token, int *quoted)
{
	char	*filename;

	if (filename_token->type == TOKEN_DQUOTE
		|| filename_token->type == TOKEN_SQUOTE)
	{
		*quoted = 1;
		filename = ft_strdup(filename_token->value);
	}
	else if (filename_token->type == TOKEN_ENV_VAR)
		filename = ft_strjoin_safe("$", filename_token->value);
	else
		filename = ft_strdup(filename_token->value);
	return (filename);
}

int	parse_redirection(t_parser *parser, t_command *cmd)
{
	t_token	*redir_token;
	t_token	*filename_token;
	char	*filename;
	int		quoted;

	quoted = 0;
	if (!validate_redir_syntax(parser))
		return (PARSE_SYNTAX_ERROR);
	redir_token = parser_peek(parser, -1);
	filename_token = parser_peek(parser, 0);
	if (redir_token->type == TOKEN_HEREDOC)
	{
		check_heredoc_quotes(parser, filename_token, &quoted);
		filename = handle_heredoc_filename(filename_token, &quoted);
	}
	else
		filename = expand_token_value_basic(filename_token);
	if (!filename)
		filename = ft_strdup("");
	parser_consume(parser);
	filename = merge_adjacent_tokens(parser, filename, filename_token);
	if (!filename || !add_redir(redir_token->type, filename, cmd, quoted))
	{
		free(filename);
		return (PARSE_MALLOC_ERROR);
	}
	return (PARSE_SUCCESS);
}
