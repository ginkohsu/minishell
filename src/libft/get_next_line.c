/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:05 by jinxu             #+#    #+#             */
/*   Updated: 2025/08/12 16:04:14 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	fill_line(int fd, char **left_over, char *buffer)
{
	ssize_t	bts;
	char	*temp;

	while (*left_over == NULL || !ft_strchr(*left_over, '\n'))
	{
		bts = read(fd, buffer, BUFFER_SIZE);
		if (bts < 0)
		{
			free(*left_over);
			*left_over = NULL;
			return (-1);
		}
		if (bts == 0)
			break ;
		buffer[bts] = '\0';
		temp = *left_over;
		*left_over = ft_strjoin_safe(temp, buffer);
		free(temp);
		if (!(*left_over))
			return (-1);
	}
	return (1);
}

char	*extract_line(char *str)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	return (ft_substr(str, 0, len));
}

char	*keep_remain(char *str)
{
	size_t	len;
	char	*remain_line;
	size_t	total_len;

	if (!str)
		return (NULL);
	total_len = ft_strlen_z(str);
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	if (!str[len])
		remain_line = NULL;
	else
		remain_line = ft_substr(str, len, total_len - len);
	return (remain_line);
}

char	*get_next_line(int fd)
{
	static char	*remain[FD_MAX];
	char		*buffer;
	char		*line;
	char		*temp;
	int			check;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	check = fill_line(fd, &remain[fd], buffer);
	free(buffer);
	if (check < 0)
	{
		free(remain[fd]);
		remain[fd] = NULL;
	}
	if ((check < 0) || (!remain[fd]))
		return (NULL);
	line = extract_line(remain[fd]);
	temp = remain[fd];
	remain[fd] = keep_remain(temp);
	free(temp);
	return (line);
}

/* 
* When fd is empty file, or EOF reached and no leftover
* remain[fd]  == NULL
*
*/
