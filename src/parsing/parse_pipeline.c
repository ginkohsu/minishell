/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:41:59 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/19 19:14:43 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirect_syntax(t_parser *parser)
{
	int		i;
	t_token	*next_token;

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

static int	check_pipe_syntax(t_parser *parser)
{
	int	i;

	i = 0;
	if (parser->token_count > 0 && parser->tokens[0].type == TOKEN_PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	while (i < parser->token_count)
	{
		if (parser->tokens[i].type == TOKEN_PIPE)
		{
			if ((i == parser->token_count - 1) || (i + 1 < parser->token_count
					&& parser->tokens[i + 1].type == TOKEN_PIPE))
			{
				printf("syntax error near unexpected token `|'\n");
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
	char	*tmp;

	if (check_pipe_syntax(parser) || check_redirect_syntax(parser))
	{
		tmp = ft_strdup("?=2");
		if (!tmp)
			return (NULL);
		if (addenv(tmp) == -1)
			exittool(ERR_ENV_CORRUPT, tmp, F_OBJ, 1);
		else
			free(tmp);
		return (NULL);
	}
	left = parse_command(parser);
	if (!left)
		return (NULL);
	token = parser_peek(parser, 0);
	if (token && token->type == TOKEN_PIPE)
		return (handle_pipe_expression(parser, left));
	return (left);
}
