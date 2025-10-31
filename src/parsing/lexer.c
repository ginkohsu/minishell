/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:16:48 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/29 10:26:28 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_special_char(char **input,
			 t_token *collected_tokens, int *count)
{
	char current;

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

static void	handle_word_char(char **input,
			t_token *collected_tokens, int *count)
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

static int	process_and_check_quote(char **input_ptr, 
			t_token *collected_tokens, int *count)
{
	if (check_unclosed_quote(*input_ptr))
	{
		printf("syntax error: unclosed quote\n");
		return (0);
	}
	if (is_special_char(**input_ptr))
		handle_special_char(input_ptr, collected_tokens, count);
	else
		handle_word_char(input_ptr, collected_tokens, count);
	return (1);
/*	{
		value = malloc(2);
		if (!value)
			return ;  //???error handling
		value[0] = **input;
		value[1] = '\0';
		collected_tokens[*count].type = get_token_type(**input);
		collected_tokens[*count].value = value;
		(*count)++;
		(*input)++;
	}
	else
	{
		word =extract_word(input);
		if (word)
		{
			collected_tokens[*count].type = TOKEN_WORD;
			collected_tokens[*count].value = word;
			(*count)++;
		}
	} 
*/
}

static t_token	*copy_to_heap(t_token *collected,
				int count, int *token_count)
{
	t_token	*heap_tokens;
	int		i;

	if (!collected || !count)
		return (NULL);
	heap_tokens = malloc (count * sizeof(t_token));
	if (!heap_tokens)
		return (NULL); // ????????ERROR HANDLING
	i = 0;
	while (i < count)
	{
		heap_tokens[i] = collected[i];
		i++;
	}
	*token_count = count;
	return (heap_tokens);
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
		if(!process_and_check_quote(&input_ptr, collected_tokens, &count))
		{
			cleanup_stack_tokens(collected_tokens, count);
			return (NULL);
		}
	}
	collected_tokens[count].type = TOKEN_EOF;
	collected_tokens[count].value = NULL;
	count++;
	if (*input_ptr && count == MAX_TOKENS)
		printf("warnng:truncated after %d tokens\n", MAX_TOKENS - 1);
	return (copy_to_heap(collected_tokens, count, token_count));
}
