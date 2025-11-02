/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:25:43 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/26 21:13:30 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_env_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '_');
}

char	*handle_env_var(char **input)
{
	char	*start;
	int		len;
	char	*var_name;

	(*input)++;
	if (**input == '?')
	{
		(*input)++;
		return (ft_strdup("?"));
	}
	start = *input;
	len = 0;
	while (**input && is_env_var_char(**input))
	{
		(*input)++;
		len++;
	}
	if (len == 0)
		return (ft_strdup("$"));
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, start, (size_t)(len + 1));
	return (var_name);
}

void	handle_env_var_char(char **input, t_token *collected_tokens, int *count)
{
	char	*var_name;

	var_name = handle_env_var(input);
	if (var_name)
	{
		if (ft_strcmp(var_name, "?") == 0)
		{
			collected_tokens[*count].type = TOKEN_EXIT_STATUS;
			collected_tokens[*count].value = var_name;
		}
		else
		{
			collected_tokens[*count].type = TOKEN_ENV_VAR;
			collected_tokens[*count].value = var_name;
		}
		(*count)++;
	}
}
