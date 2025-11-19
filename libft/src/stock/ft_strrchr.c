/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:27:33 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/13 21:32:15 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	ssize_t	i;

	if (!s)
		return (NULL);
	if (!c)
		return ((char *)&s[ft_strlen(s)]);
	i = ft_strlen(s);
	while (i--)
		if (s[i] == c)
			return ((char *)&s[i]);
	return (NULL);
}
