/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:23:35 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/13 21:23:58 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	if (!c)
		return ((char *)&s[ft_strlen(s)]);
	i = -1;
	while (s[++i])
		if (s[i] == c)
			return ((char *)&s[i]);
	return (NULL);
}
