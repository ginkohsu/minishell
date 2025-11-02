/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:15:21 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/02 20:36:14 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	parser_init(t_token *tokens, int count)
{
	t_parser	parser;

	parser.tokens = tokens;
	parser.token_count = count;
	parser.current_pos = 0;
	return (parser);
}

t_token	*parser_peek(t_parser *parser, int offset)
{
	int	pos;

	pos = parser->current_pos + offset;
	if (pos < parser->token_count)
		return (&(parser->tokens[pos]));
	return (NULL);
}

t_token	*parser_consume(t_parser *parser)
{
	t_token	*token;

	if (parser->current_pos < parser->token_count)
	{
		token = &(parser->tokens[parser->current_pos]);
		parser->current_pos++;
		return (token);
	}
	return (NULL);
}

int	parser_check(t_parser *parser, t_token_type type)
{
	t_token	*token;

	token = parser_peek(parser, 0);
	return (token && token->type == type);
}

void	set_no_space_after(t_token *token, char *input_after_token)
{
	if (*input_after_token && !ft_isspace(*input_after_token))
		token->no_space_after = 1;
	else
		token->no_space_after = 0;
}
