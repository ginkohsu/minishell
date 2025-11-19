/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 04:59:21 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 04:59:46 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest < src)
	{
		i = -1;
		while (++i < n)
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	}
	if (src < dest)
	{
		i = n;
		while (i--)
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	}
	return (dest);
}
