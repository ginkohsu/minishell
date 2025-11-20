/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:04:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/20 02:25:58 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

static void	sighandler(int sig)
{
	(void)sig;
	g_signal = 0;
	write(STDOUT_FILENO, "\n", 1);
}

static bool	writing(int fd, t_redir *r, char **line)
{
	char	*expanded;
	int		len;

	*line = get_next_line(STDIN_FILENO);
	if (g_signal == 0)
	{
		safe_free((void **)line);
		return (false);
	}
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

	line = NULL;
	file = make_tmpfile();
	if (!file)
		return (NULL);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		safe_free((void **)&file);
	while (file && writing(fd, r, &line))
	{
		if (g_signal == 0)
		{
			unlink(file);
			safe_free((void **)file);
			break ;
		}
	}
	safe_close(&fd);
	safe_free((void **)&line);
	return (file);
}

static void	in_session(bool val, struct sigaction *old_sa,
		struct sigaction *old_quit, struct termios *old_term)
{
	struct sigaction	sa;
	struct termios		term;

	if (val)
	{
		tcgetattr(STDIN_FILENO, old_term);
		term = *old_term;
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		ft_memset(&sa, 0, sizeof(sa));
		ft_memset(old_sa, 0, sizeof(*old_sa));
		ft_memset(old_quit, 0, sizeof(*old_quit));
		sa.sa_handler = sighandler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, old_sa);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, old_quit);
		return ;
	}
	sigaction(SIGINT, old_sa, NULL);
	sigaction(SIGQUIT, old_quit, NULL);
	tcsetattr(STDIN_FILENO, TCSANOW, old_term);
}

void	heredoc(t_redir *redirs)
{
	struct sigaction	old_sa;
	struct sigaction	old_quit;
	struct termios		old_term;
	t_redir				*curr;
	char				*file;

	in_session(true, &old_sa, &old_quit, &old_term);
	g_signal = 1;
	curr = redirs;
	while (curr && g_signal)
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
	in_session(false, &old_sa, &old_quit, &old_term);
}
