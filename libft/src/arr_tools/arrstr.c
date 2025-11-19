/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 05:54:22 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 06:04:29 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**arrstr(char **a, const char *s)
{
	size_t	i;

	if (!a || !s)
		return (NULL);
	i = -1;
	while (a[++i])
		if (ft_strcmp(a[i], s) == 0)
			return (&a[i]);
	return (NULL);
}
