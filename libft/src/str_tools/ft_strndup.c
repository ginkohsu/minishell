/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:43:37 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/13 21:45:27 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len > n)
		len = n;
	dup = malloc((n + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	(void)ft_strlcpy(dup, s, len + 1);
	return (dup);
}
