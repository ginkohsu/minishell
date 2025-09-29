/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:29:57 by aloimusa          #+#    #+#             */
/*   Updated: 2025/06/19 16:30:15 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	if (len > n)
		len = n;
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	(void)ft_strlcpy(dup, s, len + 1);
	return (dup);
}
