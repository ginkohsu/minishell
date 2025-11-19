/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrndup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 05:50:37 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 05:50:54 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**arrndup(char **src, size_t n)
{
	char	**dst;
	size_t	i;

	if (!src)
		return (NULL);
	dst = malloc((n + 1) * sizeof(char *));
	if (!dst)
		return (NULL);
	i = -1;
	while (src[++i] && i < n)
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
