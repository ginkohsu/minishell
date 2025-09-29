/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:58:21 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/29 10:37:15 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_quoted_content(char **input, char quote_char)
{
	char	*start;
	int		len;
	char	*content;

	(*input)++;
	start = *input;
	len = 0;
	while (**input && **input != quote_char)
	{
		(*input)++;
		len++;
	}
	if (**input == quote_char)
	{
		content = malloc(len + 1);
		if (!content)
			return (NULL); //ERROR HANDLING???????
		ft_strlcpy(content, start, (size_t)(len + 1));
		(*input)++;
		return (content);
	}
	printf("Error: Unclosed quote\n");
	return (NULL);
}

void	handle_quote_char(char **input, t_token *collected_tokens, int *count)
{
		char			current;
		char			*quoted_content;
		t_token_type	type;

		current = **input;
		quoted_content = handle_quoted_content(input, current);
		if (quoted_content)
		{
			if (current == '\'')
				type = TOKEN_SQUOTE;
			else
				type = TOKEN_DQUOTE;
			collected_tokens[*count].type = type;
			collected_tokens[*count].value = quoted_content;
			(*count)++;
		}
}
