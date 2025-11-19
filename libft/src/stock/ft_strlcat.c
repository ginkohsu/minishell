/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:36:40 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/13 21:39:08 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	if (!size)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (size <= dstlen)
		return (srclen + size);
	i = -1;
	while (src[++i] && dstlen + i < size - 1)
		dst[dstlen + i] = src[i];
	dst[dstlen + i] = '\0';
	return (srclen + dstlen);
}
