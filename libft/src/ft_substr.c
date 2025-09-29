/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:08:03 by aloimusa          #+#    #+#             */
/*   Updated: 2025/04/28 17:55:05 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		sub = malloc(1 * sizeof(char));
		sub[0] = '\0';
		return (sub);
	}
	i = (size_t)start;
	j = i;
	while (s[i] && i - j < len)
		i++;
	sub = malloc((i - j + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (s[j] && i < len)
		sub[i++] = s[j++];
	sub[i] = '\0';
	return (sub);
}
