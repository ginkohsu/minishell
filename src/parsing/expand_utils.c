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

char	*getenvstr(char *var)
{
	char	**env;

	env = fetchenv(var);
	if (env && env[0])
		return (ft_strdup(env[0] + ft_strlen(var) + 1));
	if (var[0] == '?' && !var[1])
		return (ft_strdup("0"));
	return (ft_strdup(""));
}

char	*expand_token_value_basic(t_token *token)
{
	if (token->type == TOKEN_SQUOTE)
		return (ft_strdup(token->value));
	if (token->type == TOKEN_ENV_VAR)
		return (getenvstr(token->value));
	else if (token->type == TOKEN_EXIT_STATUS)
		return (getenvstr("?"));
	else if (token->type == TOKEN_DQUOTE)
		return (expand_vars_dquote(token->value));
	else
		return (ft_strdup(token->value));
}
