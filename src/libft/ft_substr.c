/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:33:38 by jinxu             #+#    #+#             */
/*   Updated: 2025/08/12 01:51:06 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	actl_len;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen_z(s) < start)
		return (ft_strdup(""));
	actl_len = ft_strlen_z(s) - start;
	if (actl_len > len)
		actl_len = len;
	subs = malloc (actl_len + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (i < actl_len)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

/* if the start index is greater than the length of the original
    string we return an allocated empty string
	that can be freed  later on   */
