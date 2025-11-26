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

static bool	handle_line(char **line, t_redir *r)
{
	char	*expanded;
	int		len;

	len = ft_strlen(*line);
	if (len > 0 && (*line)[len - 1] == '\n')
		(*line)[len - 1] = '\0';
	if (ft_strcmp(r->filename, *line) == 0)
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
	return (true);
}

static bool	writing(int fd, t_redir *r, char **line)
{
	if (isatty(STDIN_FILENO))
		*line = readline("> ");
	else
		*line = get_next_line(STDIN_FILENO);
	if (g_signal == SIGINT)
		return (g_signal = 0, false);
	if (!*line || !handle_line(line, r))
		return (false);
	ft_fprintf(fd, "%s\n", *line);
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
		return (safe_free((void **)&file), NULL);
	while (file && writing(fd, r, &line))
		if (g_signal == SIGINT)
			break ;
	safe_close(&fd);
	safe_free((void **)&line);
	if (g_signal == SIGINT)
		return (unlink(file), safe_free((void **)&file), NULL);
	return (file);
}

void	heredoc(t_redir *redirs)
{
	struct sigaction	old_sa;
	t_redir				*curr;
	char				*file;

	in_session(true, &old_sa);
	curr = redirs;
	while (curr && g_signal != SIGINT)
	{
		if (curr->type == TOKEN_HEREDOC)
		{
			file = write_file(curr);
			if (!file)
			{
				cleanup_heredocs(redirs, curr);
				break ;
			}
			free(curr->filename);
			curr->filename = file;
		}
		curr = curr->next;
	}
	in_session(false, &old_sa);
}
