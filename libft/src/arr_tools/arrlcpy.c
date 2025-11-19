/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 05:41:03 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 05:50:13 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	arrlcpy(char **dst, char **src, size_t size)
{
	size_t	i;

	i = -1;
	if (size)
	{
		while (src[++i] && i < size - 1)
			dst[i] = src[i];
		dst[i] = NULL;
	}
	return (arrlen(src));
}
