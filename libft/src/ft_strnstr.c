/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:53:57 by aloimusa          #+#    #+#             */
/*   Updated: 2025/04/28 17:50:23 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *f, size_t n)
{
	size_t	i;
	int		f_len;

	if (!f)
		return ((char *)s);
	if (n == 0)
		return (NULL);
	f_len = ft_strlen(f);
	i = 0;
	while (s[i] && n >= (size_t)f_len + i)
	{
		if (ft_strncmp(&s[i], f, f_len) == 0)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
