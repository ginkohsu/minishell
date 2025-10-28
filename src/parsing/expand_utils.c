/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:27:32 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/26 21:17:34 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_simple_env_var(char *var_name)
{
	char	*value;

	if(ft_strcmp(var_name, "?") == 0)
		return (ft_strdup("0"));
	value = getenv(var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*expand_token_value_basic(t_token *token)
{
	if (token->type == TOKEN_SQUOTE)
		return (ft_strdup(token->value));
	if (token->type == TOKEN_ENV_VAR)
		return (expand_simple_env_var(token->value));
	else if (token->type == TOKEN_EXIT_STATUS)
		return (expand_simple_env_var("?"));
	else if (token->type == TOKEN_DQUOTE)
		return (expand_vars_dquote(token->value));
	else
		return (ft_strdup(token->value));
}

