/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 04:12:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 04:14:17 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s = malloc((s1len + s2len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	(void)ft_strlcpy(s, s1, s1len + 1);
	(void)ft_strlcpy(&s[s1len], s2, s2len + 1);
	return (s);
}
