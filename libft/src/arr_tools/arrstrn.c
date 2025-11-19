/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrstrn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 06:06:35 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 06:06:48 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**arrstrn(char **a, const char *s, size_t n)
{
	size_t	i;

	if (!a || !s)
		return (NULL);
	i = -1;
	while (a[++i])
		if (ft_strncmp(a[i], s, n) == 0)
			return (&a[i]);
	return (NULL);
}
