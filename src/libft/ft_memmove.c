/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:04:26 by jinxu             #+#    #+#             */
/*   Updated: 2025/04/29 15:18:59 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*temp_dest;
	const unsigned char	*temp_src;
	size_t				i;

	temp_dest = (unsigned char *)dest;
	temp_src = (const unsigned char *)src;
	i = 0;
	while (temp_dest > temp_src && n > i)
	{
		temp_dest[n - 1 - i] = temp_src[n - 1 - i];
		i++;
	}
	i = 0;
	while (temp_dest < temp_src && n > i)
	{
		temp_dest[i] = temp_src[i];
		i++;
	}
	return (dest);
}

/*
	The C standard says it is undefined behavior to 
	dereference a NULL pointer. 
	Accessing  memory through a NULL pointer
	(read or write) is invalid(segmentation fault).
*/
