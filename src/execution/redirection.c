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

#include "execution.h"
#include <unistd.h>

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

// read heredoc input until delimiter
static bool	heredoc(char *delimiter)
{
	int		tmp;
	int		len;
	char	*input;

	tmp = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp == -1)
		exittool(ERR_OPEN, NULL, F_AST | F_ENV | STRERR, 1);
	len = ft_strlen(delimiter);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (!input || (ft_strncmp(delimiter, input, len) == 0
				&& input[len] == '\n'))
			break ;
		write(tmp, input, ft_strlen(input));
		free(input);
	}
	safe_close(&tmp);
	if (input)
		free(input);
	redirect("/tmp/minishell_heredoc", O_RDONLY, 0, STDIN_FILENO);
	return (true);
}

// apply all redirections in linked list
void	setup_redirections(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == TOKEN_HEREDOC)
			heredoc(redirs->filename);
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
