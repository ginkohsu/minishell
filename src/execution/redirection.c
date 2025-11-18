/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 03:54:41 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/12 16:04:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		safe_close(&fd);
		exittool(ERR_DUP2, NULL, F_AST | F_ENV | STRERR, 1);
	}
	safe_close(&fd);
}

// apply all redirections in linked list
void	setup_redirections(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == TOKEN_HEREDOC)
		{
			redirect(redirs->filename, O_RDONLY, 0, STDIN_FILENO);
			unlink(redirs->filename);
		}
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
