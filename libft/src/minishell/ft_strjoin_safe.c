/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_safe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:57:40 by jinxu             #+#    #+#             */
/*   Updated: 2025/08/12 01:55:33 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_safe(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	len1 = ft_strlen_z(s1);
	len2 = ft_strlen_z(s2);
	if ((len1 > SIZE_MAX - len2 - 1) || (len1 == 0 && len2 == 0))
		return (NULL);
	str = malloc (len1 + len2 + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && (i < len1))
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && (j < len2))
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
