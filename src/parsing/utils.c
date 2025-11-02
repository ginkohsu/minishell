/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:26:55 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/26 21:51:00 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

int	is_only_whitespace(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

void	skip_whitespace(char **input)
{
	while (**input && ft_isspace(**input))
		(*input)++;
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '"'
		|| c == '$');
}

//// below functins for testing
const char	*get_token_type_name(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_PIPE)
		return ("PIPE");
	if (type == TOKEN_REDIR_IN)
		return ("REDIR_IN");
	if (type == TOKEN_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == TOKEN_REDIR_APPEND)
		return ("REDIR_APPEND");
	if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	if (type == TOKEN_SQUOTE)
		return ("SQUOTE");
	if (type == TOKEN_DQUOTE)
		return ("DQUOTE");
	if (type == TOKEN_ENV_VAR)
		return ("ENV_VAR");
	if (type == TOKEN_EXIT_STATUS)
		return ("EXIT_STATUS");
	if (type == TOKEN_EOF)
		return ("EOF");
	return ("UNKNOWN");
}

/// testing for priting tokens
void	print_tokens_debug(t_token *tokens, int count)
{
	if (!tokens)
		return ;
	printf("=== Lexer Debug Output ===\n");
	printf("Token count: %d\n", count);
	for (int i = 0; i < count; i++)
	{
		printf("[%2d] %-10s: '%s'\n", i, get_token_type_name(tokens[i].type),
			tokens[i].value ? tokens[i].value : "NULL");
	}
	printf("==========================\n");
}
