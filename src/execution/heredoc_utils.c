/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:17:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/13 17:17:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*g_hex = "0123456789abcdef";

char	*make_tmpfile(void)
{
	int		fd;
	char	buf[8];
	char	*name;
	char	suffix[18];
	int		i;

	name = ft_strdup("/tmp/minishell_heredoc");
	if (!name)
		return (NULL);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1 || read(fd, buf, 8) != 8)
	{
		safe_close(&fd);
		return (name);
	}
	safe_close(&fd);
	suffix[0] = '_';
	suffix[17] = '\0';
	i = -1;
	while (++i < 8)
	{
		suffix[1 + i * 2] = g_hex[(unsigned char)buf[i] >> 4];
		suffix[2 + i * 2] = g_hex[(unsigned char)buf[i] & 0xf];
	}
	return (ft_strapp(name, suffix));
}
