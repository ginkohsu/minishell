/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_dquote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 21:08:01 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/26 21:15:51 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_one_var(char **src)
{
	char	*name;
	char	*val;
	char	*env;

	name = handle_env_var(src);
	if (ft_strcmp(name, "$") == 0)
		return (name); // literal '$', return as-is
	if (ft_strcmp(name, "?") == 0)
		val = ft_itoa(g_exit_status);
	else
	{
		env = getenv(name);
		if (env)
			val = ft_strdup(env);
		else
			val = ft_strdup("");
	}
	free(name);
	return (val);
}

char	*expand_vars_dquote(char *src)
{
    char	*res;
    char	*tmp;
	char	*join_tmp;

	res = ft_strdup("");
	while (*src)
	{
		if (*src == '$' && *(src + 1))
			tmp = expand_one_var(&src);
		else
		{
			tmp = ft_substr(src, 0, 1);
			src++;
        }
        // Append and free only the first argument (res)
        {
			join_tmp = ft_strjoin_safe(res, tmp);
			free(res);
			res = join_tmp;
		}
		free(tmp);
	}
    return res;
}
