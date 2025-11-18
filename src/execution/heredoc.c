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

static void	sighandler(int sig)
{
	(void)sig;
	g_signal = 0;
	write(STDOUT_FILENO, "\n", 1);
}

static bool	writing(int fd, t_redir *r, char **line)
{
	char	*expanded;

	*line = readline("");
	if (!*line || ft_strcmp(r->filename, *line) == 0 || g_signal == 0)
	{
		if (*line)
			free(*line);
		return (false);
	}
	if (!r->quoted)
	{
		expanded = expand_vars_dquote(*line);
		if (expanded)
		{
			free(*line);
			*line = expanded;
		}
	}
	write(fd, *line, ft_strlen(*line));
	write(fd, "\n", 1);
	free(*line);
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
		free(file);
		return (NULL);
	}
	while (writing(fd, r, &line))
	{
		if (g_signal == 0)
		{
			unlink(file);
			break ;
		}
	}
	close(fd);
	return (file);
}

static bool	cleanup_heredocs(t_redir *start, t_redir *end)
{
	while (start && start != end)
	{
		if (start->type == TOKEN_HEREDOC && start->filename)
			unlink(start->filename);
		start = start->next;
	}
	return (true);
}

void	heredoc(t_redir *redirs)
{
	struct sigaction	sa;
	struct sigaction	old_sa;
	t_redir				*curr;
	char				*file;

	sa.sa_handler = sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, &old_sa);
	curr = redirs;
	while (curr)
	{
		if (curr->type == TOKEN_HEREDOC)
		{
			file = write_file(curr);
			if (!file && cleanup_heredocs(redirs, curr))
				break ;
			free(curr->filename);
			curr->filename = file;
		}
		curr = curr->next;
	}
	sigaction(SIGINT, &old_sa, NULL);
}
