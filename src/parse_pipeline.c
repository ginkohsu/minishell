/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:41:59 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/17 23:46:44 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

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
	
	left = parse_command(parser);
	if (!left)
		return (NULL);
	token = parser_peek(parser, 0);
	if (token && token->type == TOKEN_PIPE)
		return (handle_pipe_expression(parser, left));
	return (left);
}
