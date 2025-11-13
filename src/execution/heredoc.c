/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:04:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/12 16:04:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char		*g_hex_digits = "0123456789abcdef";
static struct sigaction	g_old_action;

extern volatile sig_atomic_t	g_signal;

static void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	g_signal = 0;
	write(STDOUT_FILENO, "\n", 1);
}

static void	signal_setup(void)
{
	struct sigaction	action;

	action.sa_handler = heredoc_sigint_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGINT, &action, &g_old_action);
}

static void	signal_restore(void)
{
	sigaction(SIGINT, &g_old_action, NULL);
}

static void	cleanup(int *fd, char *filename)
{
	if (fd && *fd >= 0)
		safe_close(fd);
	if (filename)
		unlink(filename);
}

// generate unique heredoc filename with urandom suffix
static char	*gen_heredoc_name(void)
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
		suffix[1 + i * 2] = g_hex_digits[(unsigned char)buf[i] >> 4];
		suffix[2 + i * 2] = g_hex_digits[(unsigned char)buf[i] & 0xf];
	}
	return (ft_strapp(name, suffix));
}

// write one line to heredoc file, return false if delimiter reached
static bool	writing(int fd, t_redir *redir, char **input)
{
	char	*expanded;
	int		len;

	*input = get_next_line(STDIN_FILENO);
	len = ft_strlen(redir->filename);
	if (!*input || (ft_strncmp(redir->filename, *input, len) == 0
			&& (*input)[len] == '\n'))
		return (false);
	if (!redir->quoted)
	{
		expanded = expand_vars_dquote(*input);
		if (expanded)
		{
			free(*input);
			*input = expanded;
		}
	}
	write(fd, *input, ft_strlen(*input));
	free(*input);
	return (true);
}

// read heredoc input until delimiter, handle signal interruption
static char	*process(t_redir *redir)
{
	int		tmp;
	char	*input;
	char	*filename;

	filename = gen_heredoc_name();
	if (!filename)
		exittool(ERR_MALLOC, NULL, F_AST | F_ENV | STRERR, 1);
	tmp = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp == -1)
		exittool(ERR_OPEN, filename, F_AST | F_ENV | F_OBJ | STRERR, 1);
	while (writing(tmp, redir, &input))
	{
		if (g_signal == 0)
		{
			cleanup(&tmp, filename);
			free(filename);
			signal_restore();
			exittool(NULL, NULL, F_AST | F_ENV, 130);
		}
	}
	safe_close(&tmp);
	if (input)
		free(input);
	return (filename);
}

// process all heredocs, return filename of last one
char	*setup_heredocs(t_redir *redirs)
{
	t_redir	*curr;
	char	*last_file;
	char	*new_file;

	last_file = NULL;
	curr = redirs;
	signal_setup();
	while (curr)
	{
		if (curr->type == TOKEN_HEREDOC)
		{
			new_file = process(curr);
			if (last_file)
			{
				unlink(last_file);
				free(last_file);
			}
			last_file = new_file;
		}
		curr = curr->next;
	}
	signal_restore();
	return (last_file);
}
