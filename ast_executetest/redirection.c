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

static void	redirect(char *file, int oflag, int perms, int io)
{
	int	fd;

	if (perms)
		fd = open(file, oflag, perms);
	else
		fd = open(file, oflag);
	if (fd == -1)
		ft_error(NULL, file, F_AST | OPEN_FAIL, 0);
	if (dup2(fd, io) == -1)
		ft_error("dup2", NULL, F_AST | STRERROR, 1);
	close(fd);
	fd = -1;
}

static bool	heredoc(char *delimiter)
{
	int		tmp;
	int		len;
	char	*input;

	tmp = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp == -1)
		ft_error("open: %s", NULL, F_AST | STRERROR, 1);
	close(tmp);
	len = ft_strlen(delimiter);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (!input)
			break ;
		if (ft_strcmp(delimiter, input) == 0 && input[len] == '\n')
			break ;
		write(tmp, input, len);
	}
	if (input)
		free(input);
	return (true);
}

void	setup_redirections(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == REDIR_HEREDOC)
			heredoc(redirs->filename);
		else if (redirs->type == REDIR_IN)
			redirect(redirs->filename, O_RDONLY, 0, STDIN_FILENO);
		else if (redirs->type == REDIR_OUT)
			redirect(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644,
				STDOUT_FILENO);
		else if (redirs->type == REDIR_APPEND)
			redirect(redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644,
				STDOUT_FILENO);
		redirs = redirs->next;
	}
}
