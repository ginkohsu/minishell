/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:57:11 by aloimusa          #+#    #+#             */
/*   Updated: 2025/04/28 17:49:02 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	if (s)
	{
		len = ft_strlen(s);
		if (write(fd, s, len))
			return (write(fd, "\n", 1) + len);
	}
	return (write(fd, "\n", 1));
}
