/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 05:15:23 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 05:17:09 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *f, size_t n)
{
	size_t	i;
	int		f_len;

	if (!f)
		return ((char *)s);
	f_len = ft_strlen(f);
	if (!f_len)
		return ((char *)s);
	if (!n)
		return (NULL);
	i = -1;
	while (s[++i] && n >= f_len + i)
		if (ft_strncmp(&s[i], f, f_len) == 0)
			return ((char *)&s[i]);
	return (NULL);
}
