/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:26:55 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/23 16:07:41 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' 
			|| c == '\r' || c == '\v' ||  c == '\f');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' ||  c == '\'' || c == '"');
}

t_token_type	get_token_type(char c)
{
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '<')
		return (TOKEN_REDIR_IN);
	if (c == '>')
		return (TOKEN_REDIR_OUT);
	
	return TOKEN_WORD;
}

//// below functins for testing only: ////////////////
static const char *get_token_type_name(t_token_type type) {
if (type == TOKEN_WORD) return "WORD";
if (type == TOKEN_PIPE) return "PIPE";
if (type == TOKEN_REDIR_IN) return "REDIR_IN";
if (type == TOKEN_REDIR_OUT) return "REDIR_OUT";
if (type == TOKEN_EOF) return "EOF";
return "UNKNOWN";
}

///testing for priting tokens
void print_tokens_debug(t_token *tokens, int count) {
if (!tokens) return;

printf("=== Lexer Debug Output ===\n");
printf("Token count: %d\n", count);

for (int i = 0; i < count; i++) {
printf("[%2d] %-10s: '%s'\n",
i,
get_token_type_name(tokens[i].type),
tokens[i].value ? tokens[i].value : "NULL");
}
printf("==========================\n");
}
