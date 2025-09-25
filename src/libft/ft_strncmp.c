/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:03:16 by jinxu             #+#    #+#             */
/*   Updated: 2025/04/24 20:48:53 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/* Always cast to unsigned char when you’re doing comparisons
based on ASCII or byte values, because that’s the only way 
to guarantee values from 0 to 255.

return ((unsigned char)s1[i] - (unsigned char)s2[i]);
This way, 'ÿ' will always be 255, not -1.
*/
