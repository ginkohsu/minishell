/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:04:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/12 16:28:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char		*g_hex = "0123456789abcdef";
static struct sigaction	g_old_sa;

extern volatile sig_atomic_t	g_signal;

static void	sighandler(int sig)
{
	(void)sig;
	g_signal = 0;
	write(STDOUT_FILENO, "\n", 1);
}

static char	*make_tmpfile(void)
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

static bool	writing(int fd, t_redir *r, char **line)
{
	char	*expanded;
	int		len;

	*line = get_next_line(STDIN_FILENO);
	len = ft_strlen(r->filename);
	if (!*line || (ft_strncmp(r->filename, *line, len) == 0
			&& (*line)[len] == '\n'))
		return (false);
	if (!r->quoted)
	{
		expanded = expand_vars_dquote(*line);
		if (expanded)
		{
			safe_free((void **)line);
			*line = expanded;
		}
	}
	write(fd, *line, ft_strlen(*line));
	safe_free((void **)line);
	return (true);
}

static char	*write_file(t_redir *r)
{
	int		fd;
	char	*line;
	char	*file;

	file = make_tmpfile();
	if (!file)
		return (NULL);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		safe_free((void **)&file);
		return (NULL);
	}
	while (writing(fd, r, &line))
	{
		if (g_signal == 0)
		{
			safe_close(&fd);
			unlink(file);
			safe_free((void **)&file);
			return (NULL);
		}
	}
	safe_close(&fd);
	safe_free((void **)&line);
	return (file);
}

static void	cleanup_heredocs(t_redir *start, t_redir *end)
{
	while (start && start != end)
	{
		if (start->type == TOKEN_HEREDOC && start->filename)
			unlink(start->filename);
		start = start->next;
	}
}

void	heredoc(t_redir *redirs)
{
	struct sigaction	sa;
	t_redir				*curr;
	char				*delim;
	char				*file;

	sa.sa_handler = sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, &g_old_sa);
	curr = redirs;
	while (curr)
	{
		if (curr->type == TOKEN_HEREDOC)
		{
			delim = curr->filename;
			file = write_file(curr);
			if (!file)
			{
				cleanup_heredocs(redirs, curr);
				sigaction(SIGINT, &g_old_sa, NULL);
				return ;
			}
			safe_free((void **)&delim);
			curr->filename = file;
		}
		curr = curr->next;
	}
	sigaction(SIGINT, &g_old_sa, NULL);
}
