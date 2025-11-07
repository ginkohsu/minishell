/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 03:54:41 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/22 03:54:42 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*g_hex_digits = "0123456789abcdef";

// open file and dup to stdin/stdout
static void	redirect(char *file, int oflag, int perms, int io)
{
	int	fd;

	if (perms)
		fd = open(file, oflag, perms);
	else
		fd = open(file, oflag);
	if (fd == -1)
		exittool(NULL, file, F_AST | F_ENV | OPEN_FAIL, 0);
	if (dup2(fd, io) == -1)
		exittool(ERR_DUP2, NULL, F_AST | F_ENV | STRERR, 1);
	safe_close(&fd);
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

// read heredoc input until delimiter
static void	heredoc(t_redir *redir)
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
	while (g_signal && writing(tmp, redir, &input))
		;
	safe_close(&tmp);
	if (input)
		free(input);
	if (g_signal)
		redirect(filename, O_RDONLY, 0, STDIN_FILENO);
	unlink(filename);
	free(filename);
}

// apply all redirections in linked list
void	setup_redirections(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == TOKEN_HEREDOC)
			heredoc(redirs);
		else if (redirs->type == TOKEN_REDIR_IN)
			redirect(redirs->filename, O_RDONLY, 0, STDIN_FILENO);
		else if (redirs->type == TOKEN_REDIR_OUT)
			redirect(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644,
				STDOUT_FILENO);
		else if (redirs->type == TOKEN_REDIR_APPEND)
			redirect(redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644,
				STDOUT_FILENO);
		redirs = redirs->next;
	}
}
