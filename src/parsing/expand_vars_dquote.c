/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_dquote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 21:08:01 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/02 17:32:58 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_one_var(char **src)
{
	char	*name;
	char	*val;

	name = handle_env_var(src);
	if (!name)
		return (NULL);
	if (ft_strcmp(name, "$") == 0)
		return (name);
	if (ft_strcmp(name, "?") == 0)
		val = getenvstr("?");
	else
		val = getenvstr(name);
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
		{
			join_tmp = ft_strjoin_safe(res, tmp);
			free(res);
			res = join_tmp;
		}
		free(tmp);
	}
	return (res);
}
