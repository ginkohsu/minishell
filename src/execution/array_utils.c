/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:54:29 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/16 09:54:29 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// count elements in null-terminated array (like strlen)
int	arrlen(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = -1;
	while (arr[++i])
		;
	return (i);
}

// shallow copy array pointers (like strlcpy)
int	arrlcpy(char **dst, char **src, int dstsize)
{
	int	i;
	int	srclen;

	if (!src)
		return (0);
	srclen = arrlen(src);
	if (!dst || dstsize == 0)
		return (srclen);
	i = -1;
	while (++i < dstsize - 1 && src[i])
		dst[i] = src[i];
	dst[i] = NULL;
	return (srclen);
}

// deep copy array with strdup on each element (like strdup)
char	**arrdup(char **src)
{
	if (!src)
		return (NULL);
	return (arrndup(src, arrlen(src)));
}

// deep copy n elements with strdup (like strndup)
char	**arrndup(char **src, int n)
{
	char	**dst;
	int		i;

	if (!src)
		return (NULL);
	dst = malloc((n + 1) * sizeof(char *));
	if (!dst)
		return (NULL);
	i = -1;
	while (++i < n && src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			free_array(dst);
			return (NULL);
		}
	}
	dst[i] = NULL;
	return (dst);
}

// find position of string in array (like strchr)
int	arrstr(char **arr, char *str)
{
	int	i;

	if (!arr || !str)
		return (-1);
	i = -1;
	while (arr[++i])
		if (ft_strcmp(arr[i], str) == 0)
			return (i);
	return (-1);
}
