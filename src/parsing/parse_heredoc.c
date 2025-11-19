/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:53:48 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/19 20:33:50 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_heredoc_quotes(t_parser *parser, t_token *token, int *quoted)
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

char	*handle_heredoc_filename(t_token *filename, int *quoted)
{
	char	*str;

	if (filename->type == TOKEN_DQUOTE || filename->type == TOKEN_SQUOTE)
	{
		*quoted = 1;
		str = ft_strdup(filename->value);
	}
	else if (filename->type == TOKEN_ENV_VAR)
		str = ft_strjoin_safe("$", filename->value);
	else
		str = ft_strdup(filename->value);
	return (str);
}
