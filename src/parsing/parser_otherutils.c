/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_otherutils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:19:44 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/26 21:19:57 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_HEREDOC);
}

int	is_terminating_token(t_token *token)
{
	if (!token)
		return (1);
	return (token->type == TOKEN_PIPE || token->type == TOKEN_EOF);
}

int	is_string_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_WORD || token->type == TOKEN_SQUOTE
		|| token->type == TOKEN_DQUOTE || token->type == TOKEN_ENV_VAR
		|| token->type == TOKEN_EXIT_STATUS);
}
