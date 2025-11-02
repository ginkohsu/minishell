/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:20:17 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/02 17:34:15 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirect_char(char **input, t_token *collected_tokens,
		int *count)
{
	char	current;
	char	next;

	current = **input;
	next = *(*input + 1);
	if (current == '>' && next == '>')
	{
		collected_tokens[*count].type = TOKEN_REDIR_APPEND;
		collected_tokens[*count].value = ft_strdup(">>");
		(*count)++;
		*input += 2;
	}
	else if (current == '<' && next == '<')
	{
		collected_tokens[*count].type = TOKEN_HEREDOC;
		collected_tokens[*count].value = ft_strdup("<<");
		(*count)++;
		*input += 2;
	}
	else
		handle_single_special_char(input, collected_tokens, count);
}

void	handle_single_special_char(char **input, t_token *collected_tokens,
		int *count)
{
	char			current;
	char			*value;
	t_token_type	type;

	current = **input;
	value = malloc(2);
	if (!value)
		return ;
	value[0] = current;
	value[1] = '\0';
	if (current == '|')
		type = TOKEN_PIPE;
	else if (current == '<')
		type = TOKEN_REDIR_IN;
	else if (current == '>')
		type = TOKEN_REDIR_OUT;
	else
	{
		free(value);
		return ;
	}
	collected_tokens[*count].type = type;
	collected_tokens[*count].value = value;
	(*count)++;
	(*input)++;
}
