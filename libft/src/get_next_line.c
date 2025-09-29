/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:46:01 by aloimusa          #+#    #+#             */
/*   Updated: 2025/06/19 16:46:02 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*eof(char *str);

char	*get_next_line(int fd)
{
	static char	buffer[_POSIX_OPEN_MAX][BUFFERSIZE + 1];
	char		*ptr;
	char		*str;

	if (BUFFERSIZE <= 0 || fd < 0 || fd > _POSIX_OPEN_MAX)
		return (NULL);
	str = ft_strndup(buffer[fd], ft_strlen(buffer[fd]));
	if (!str)
		return (NULL);
	ptr = ft_strchr(str, '\n');
	while (!ptr)
	{
		ft_memset(buffer[fd], '\0', BUFFERSIZE + 1);
		if (read(fd, buffer[fd], BUFFERSIZE) <= 0)
			return (eof(str));
		str = ft_strapp(str, buffer[fd]);
		if (!str)
			return (NULL);
		ptr = ft_strchr(str, '\n');
	}
	ft_strlcpy(buffer[fd], ptr + 1, BUFFERSIZE + 1);
	*(ptr + 1) = '\0';
	return (str);
}

static char	*eof(char *str)
{
	if (ft_strlen(str) > 0)
		return (str);
	free(str);
	return (NULL);
}
