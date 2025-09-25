/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:16:48 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/22 20:30:50 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	skip_whitespace(char **input)
{
	while (**input && ft_isspace(**input))
		(*input)++;
}

static char *extract_word(char **input)
{
	char	*start;
	int		len;
	char	*word;

	if (!input || !*input || !**input)
		return (NULL);
	start = *input;
	len = 0;
	while (**input && !ft_isspace(**input) && !is_special_char(**input))
	{
		(*input)++;
		len++;
	}
	if (len == 0)
		return (NULL);
	word = malloc (len + 1);
	if (!word)
		return (NULL); //??????????????ERROR HANDLING
	ft_strlcpy(word, start, (size_t)(len + 1));
	return (word);
}

static void	process_char(char **input, t_token *collected_tokens, int *count)
{
	char	*word;
	char	*value;

	if (is_special_char(**input))
	{
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
}

static t_token	*copy_to_heap(t_token *collected, int count, int *token_count)
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
		process_char(&input_ptr, collected_tokens, &count);
	}
	collected_tokens[count].type = TOKEN_EOF;
	collected_tokens[count].value = NULL;
	count++;
	if (*input_ptr && count == MAX_TOKENS)
		printf("warnng:truncated after %d tokens\n", MAX_TOKENS - 1);
	return (copy_to_heap(collected_tokens, count, token_count));
}


