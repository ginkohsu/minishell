/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:16:48 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/03 01:56:58 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_special_char(char **input, t_token *collected_tokens,
		int *count)
{
	char	current;

	current = **input;
	if (current == '>' || current == '<')
		handle_redirect_char(input, collected_tokens, count);
	else if (current == '\'' || current == '"')
		handle_quote_char(input, collected_tokens, count);
	else if (current == '$')
		handle_env_var_char(input, collected_tokens, count);
	else if (current == '|')
		handle_single_special_char(input, collected_tokens, count);
}

static void	handle_word_char(char **input, t_token *collected_tokens,
		int *count)
{
	char	*word;

	word = extract_word(input);
	if (word)
	{
		collected_tokens[*count].type = TOKEN_WORD;
		collected_tokens[*count].value = word;
		(*count)++;
	}
}

static void	process_char_with_tracking(char **input, t_token *collected_tokens,
		int *count)
{
	int	prev_count;

	prev_count = *count;
	if (is_special_char(**input))
		handle_special_char(input, collected_tokens, count);
	else
		handle_word_char(input, collected_tokens, count);
	if (*count > prev_count)
	{
		if (**input && !ft_isspace(**input))
			collected_tokens[prev_count].no_space_after = 1;
		else
			collected_tokens[prev_count].no_space_after = 0;
	}
}

static int	process_and_check_quote(char **input_ptr, t_token *collected_tokens,
		int *count)
{
	if (check_unclosed_quote(*input_ptr))
	{
		ft_fprintf(2, "syntax error: unclosed quote\n");
		return (0);
	}
	process_char_with_tracking(input_ptr, collected_tokens, count);
	return (1);
}

t_token	*tokenize(char *input, int *token_count)
{
	t_token	collected_tokens[MAX_TOKENS];
	int		count;
	char	*input_ptr;

	count = 0;
	input_ptr = input;
	while (*input_ptr && count < MAX_TOKENS - 1)
	{
		skip_whitespace(&input_ptr);
		if (!*input_ptr)
			break ;
		if (!process_and_check_quote(&input_ptr, collected_tokens, &count))
		{
			cleanup_stack_tokens(collected_tokens, count);
			return (NULL);
		}
	}
	collected_tokens[count].type = TOKEN_EOF;
	collected_tokens[count].value = NULL;
	count++;
	if (*input_ptr && count == MAX_TOKENS)
		ft_fprintf(2, "warning: truncated after %d tokens\n", MAX_TOKENS - 1);
	return (copy_to_heap(collected_tokens, count, token_count));
}
