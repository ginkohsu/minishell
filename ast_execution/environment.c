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

#include "execution.h"

static t_table	*g_table = NULL;

// get env variable by key, null returns full array
char	**fetchenv(char *key)
{
	int		i;
	size_t	len;

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
void	initenv(char **src_env)
{
	size_t	word;
	size_t	len;

	if (g_table && g_table->env)
		free_array(g_table->env);
	if (g_table)
		free(g_table);
	g_table = malloc(sizeof(t_table));
	if (!g_table)
		return ;
	word = count_array(src_env);
	g_table->env = malloc((word + 1) * sizeof(char *));
	if (!g_table->env)
		return ;
	word = -1;
	while (src_env[++word])
	{
		len = ft_strlen(src_env[word]);
		g_table->env[word] = malloc((len + 1) * sizeof(char));
		if (!g_table->env[word])
			return ;
		(void)ft_strlcpy(g_table->env[word], src_env[word], len + 1);
	}
	g_table->env[word] = NULL;
	g_table->count = word;
}

// add or update environment variable
void	addenv(char *entry)
{
	size_t	len;
	size_t	word;
	char	**new_env;

	new_env = malloc((g_table->count + 1 + (bool)(fetchenv(entry)))
			* sizeof(char *));
	if (!new_env)
		return ;
	word = -1;
	while (g_table->env[++word])
	{
		len = ft_strchr(entry, '=') - entry;
		if (ft_strncmp(entry, g_table->env[word], len) == 0
			&& g_table->env[word][len] == '=')
			continue ;
		len = ft_strlen(g_table->env[word]);
		new_env[word] = malloc((len + 1) * sizeof(char));
		if (!new_env[word])
			return ;
		(void)ft_strlcpy(new_env[word], g_table->env[word], len + 1);
	}
	new_env[word] = entry;
	new_env[++word] = NULL;
	initenv(new_env);
	free_array(new_env);
}

// remove environment variable by key
void	rmenv(char *key)
{
	size_t	len;
	size_t	word;
	size_t	entry;
	char	**new_env;

	if (!fetchenv(key))
		return ;
	new_env = malloc(g_table->count * sizeof(char *));
	if (!new_env)
		return ;
	word = -1;
	entry = -1;
	while (g_table->env[++word])
	{
		if (ft_strcmp(key, g_table->env[word]) == 0)
			continue ;
		len = ft_strlen(g_table->env[word]);
		new_env[++entry] = malloc((len + 1) * sizeof(char));
		if (!new_env[entry])
			return ;
		(void)ft_strlcpy(new_env[entry], g_table->env[word], len + 1);
	}
	new_env[++entry] = NULL;
	initenv(new_env);
	free_array(new_env);
}

// return sorted copy of environment
char	**get_sorted_env(void)
{
	char	**srtd;
	size_t	i;
	size_t	j;

	srtd = malloc((g_table->count + 1) * sizeof(char *));
	if (!srtd)
		return (NULL);
	i = -1;
	while (++i <= g_table->count)
		srtd[i] = g_table->env[i];
	i = -1;
	while (++i < g_table->count - 1)
	{
		j = i;
		while (++j < g_table->count)
		{
			if (ft_strcmp(srtd[i], srtd[j]) > 0)
			{
				srtd[i] = (char *)((uintptr_t)srtd[i] ^ (uintptr_t)srtd[j]);
				srtd[j] = (char *)((uintptr_t)srtd[i] ^ (uintptr_t)srtd[j]);
				srtd[i] = (char *)((uintptr_t)srtd[i] ^ (uintptr_t)srtd[j]);
			}
		}
	}
	return (srtd);
}
