/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:41:59 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/28 19:16:09 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*parse_from_tokens(t_token *tokens, int count)
{
	t_parser	parser;
	t_ast		*ast;
	t_token		*remaining;

	parser = parser_init(tokens, count);
	ast = parse_pipeline(&parser);
	if (!ast)
		return (NULL);
	remaining = parser_peek(&parser, 0);
	if (remaining && remaining->type != TOKEN_EOF) //unconsumed tokens at the end
	{
		printf("syntax error near '%s'\n", remaining->value);
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}

t_ast	*parse(char *input)
{
	t_ast		*ast;
	int			token_count;
	t_token		*tokens;
	
	if (!input || !*input)
		return (NULL);
	tokens = tokenize(input, &token_count);
	if (!tokens)
		return (NULL); //ERROR HANDLING?
	ast = parse_from_tokens(tokens, token_count);
	free_tokens(tokens, token_count);
	return (ast);
}
