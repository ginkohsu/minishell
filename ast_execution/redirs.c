/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:36:21 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/09 15:36:45 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <fcntl.h>
#include <unistd.h>

static bool heredoc(char *delimiter)
{
	int tmp;
	int	len;
	char *input;

	tmp = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp == -1)
		ft_error("open: %s", NULL, F_AST | STRERROR, 1);
	close(tmp);
	len = ft_strlen(delimiter);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (!input)
			break;
		if (ft_strcmp(delimiter, input) == 0 && input[len] == '\n')
			break;
		write(tmp, input, len);
	}
	if (input)
		free(input);
	return (true);
}

void	setup_redirections(t_redir *redirs)
{
	int fd;

	while (redirs)
	{
		fd = -1;
		if (redirs->type == REDIR_HEREDOC && heredoc(redirs->filename))
		{
			redirs = redirs->next;
			continue;
		}
		else if (redirs->type == REDIR_IN)
			fd = open(redirs->filename, O_RDONLY);
		else if (redirs->type == REDIR_OUT)
			fd = open(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redirs->type == REDIR_APPEND)
			fd = open(redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			ft_error(NULL, redirs->filename, F_AST | OPEN_FAIL, 0);
		if (redirs->type == REDIR_IN && dup2(fd, STDIN_FILENO) == -1)
			ft_error("dup2 failed", NULL, F_AST, 1);
		else if (dup2(fd, STDOUT_FILENO) == -1)
			ft_error("dup2 failed", NULL, F_AST, 1);
		close(fd);
		redirs = redirs->next;
	}
}
