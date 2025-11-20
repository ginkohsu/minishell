/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:02:24 by aloimusa          #+#    #+#             */
/*   Updated: 2025/09/30 17:02:30 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_table	*g_table = NULL;

// get env variable by key, null returns full array
char	**fetchenv(char *key)
{
	int	i;
	int	len;

	if (!g_table || !g_table->env)
		return (NULL);
	if (!key)
		return (g_table->env);
	len = 0;
	while (key[len] && key[len] != '=')
		len++;
	i = -1;
	while (g_table->env[++i])
		if (ft_strncmp(key, g_table->env[i], len) == 0
			&& g_table->env[i][len] == '=')
			return (&g_table->env[i]);
	return (NULL);
}

// initialize environment from array
int	initenv(char **src_env)
{
	int	len;

	if (g_table && src_env == g_table->env)
		return (0);
	if (g_table && g_table->env)
		free_array(g_table->env);
	if (g_table)
		free(g_table);
	g_table = NULL;
	if (!src_env)
		return (0);
	g_table = malloc(sizeof(t_table));
	if (!g_table)
		return (-1);
	len = arrlen(src_env);
	g_table->env = arrndup(src_env, len);
	if (!g_table->env)
	{
		free(g_table);
		g_table = NULL;
		return (-1);
	}
	g_table->size = len;
	return (0);
}

// add or update environment variable
int	addenv(char *entry)
{
	char	**ptr;
	char	**new_env;

	ptr = fetchenv(entry);
	if (ptr)
	{
		free(ptr[0]);
		ptr[0] = ft_strdup(entry);
		if (!ptr[0])
			return (-1);
		return (0);
	}
	new_env = arrndup(g_table->env, g_table->size + 1);
	if (new_env)
		new_env[g_table->size] = ft_strdup(entry);
	if (!new_env || !new_env[g_table->size])
	{
		free_array(new_env);
		return (-1);
	}
	new_env[g_table->size + 1] = NULL;
	if (initenv(new_env) == -1)
		return (-1);
	free_array(new_env);
	return (0);
}

// remove environment variable by key
int	rmenv(char *key)
{
	int	word;
	int	keylen;

	if (!fetchenv(key))
		return (0);
	keylen = ft_strlen(key);
	word = -1;
	while (g_table->env[++word])
		if (ft_strncmp(key, g_table->env[word], keylen) == 0
			&& g_table->env[word][keylen] == '=')
			break ;
	free(g_table->env[word]);
	while (g_table->env[++word])
		g_table->env[word - 1] = g_table->env[word];
	g_table->env[word - 1] = NULL;
	g_table->size--;
	return (0);
}
