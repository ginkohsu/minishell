/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:37:13 by aloimusa          #+#    #+#             */
/*   Updated: 2025/06/26 16:37:29 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strapp(char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strndup(s2, ft_strlen(s2)));
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	(void)ft_strlcpy(res, s1, len1 + 1);
	(void)ft_strlcpy(res + len1, s2, len2 + 1);
	free(s1);
	return (res);
}
