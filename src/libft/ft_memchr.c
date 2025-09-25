/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:41:54 by jinxu             #+#    #+#             */
/*   Updated: 2025/04/29 15:19:42 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		else
			ptr++;
		n--;
	}
	return (NULL);
}

/*
1.
We are relying on the assumption that 
n does not exceed the actual number of valid bytes 
in the memory block pointed to by s.
If n is too large, it can result in 
accessing invalid memory or cause an error.
2.
Without typecasting, the comparison between an int and 
an unsigned char could lead to incorrect results,
for example when int is -1.
When you cast -1 to unsigned char, it becomes 255, 
because the lowest byte (0xFF) 
represents 255 in an unsigned byte.
*/
