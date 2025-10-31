/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:41:59 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/26 21:19:29 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirect_syntax(t_parser *parser)
{
	int			i;
	t_token*	next_token;

	i = 0;
	while (i < (parser->token_count - 1))
	{
		if (is_redirection_token(&parser->tokens[i]))
		{
			next_token = &parser->tokens[i + 1];
			if (next_token->type == TOKEN_EOF)
			{
				printf("syntax error near unexpected token 'newline'\n");
				return (1);
			}
			if (!is_string_token(next_token))
			{
				printf("syntax error near unexpected token '%s'\n", 
				next_token->value);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static t_ast	*handle_pipe_expression(t_parser *parser, t_ast *left)
{
	t_ast	*right;
	
	parser_consume(parser);
	right = parse_pipeline(parser);
	if (!right)
	{
		free_ast(left);
		return (NULL);
	}
	return (create_pipe_node(left, right));
}

t_ast	*parse_pipeline(t_parser *parser)
{
	t_ast	*left;
	t_token	*token;

	if (check_redirect_syntax(parser))
		return (NULL);
	left = parse_command(parser);
	if (!left)
		return (NULL);
	token = parser_peek(parser, 0);
	if (token && token->type == TOKEN_PIPE)
		return (handle_pipe_expression(parser, left));
	return (left);
}
