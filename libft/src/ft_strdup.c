/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:50:57 by aloimusa          #+#    #+#             */
/*   Updated: 2025/04/28 17:49:35 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(src);
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	(void)ft_strlcpy(dup, src, len + 1);
	return (dup);
}
