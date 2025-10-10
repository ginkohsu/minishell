/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 21:34:02 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/09 00:37:13 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// execute single command without pipes
void	only_child(t_command *cmd, int fd[3][2])
{
	(void)fd;
	setup_redirections(cmd->redirs);
	execute_command(cmd);
}

// execute first command in pipeline
void	first_child(t_command *cmd, int fd[3][2])
{
	if (dup2(fd[NEXT][WRITE], STDOUT_FILENO) == -1)
	{
		close(fd[NEXT][READ]);
		close(fd[NEXT][WRITE]);
		ft_error("dup2", NULL, F_AST | STRERROR, 1);
	}
	close(fd[NEXT][WRITE]);
	close(fd[NEXT][READ]);
	setup_redirections(cmd->redirs);
	execute_command(cmd);
}

// execute last command in pipeline
void	last_child(t_command *cmd, int fd[3][2])
{
	close(fd[LAST][WRITE]);
	if (dup2(fd[LAST][READ], STDIN_FILENO) == -1)
		ft_error("dup2", NULL, F_AST | STRERROR, 1);
	close(fd[LAST][READ]);
	close(fd[NEXT][READ]);
	close(fd[NEXT][WRITE]);
	setup_redirections(cmd->redirs);
	execute_command(cmd);
}

// execute middle command in pipeline
void	middle_child(t_command *cmd, int fd[3][2])
{
	close(fd[LAST][WRITE]);
	if (dup2(fd[LAST][READ], STDIN_FILENO) == -1)
		ft_error("dup2", NULL, F_AST | STRERROR, 1);
	close(fd[LAST][READ]);
	close(fd[NEXT][READ]);
	if (dup2(fd[NEXT][WRITE], STDOUT_FILENO) == -1)
		ft_error("dup2", NULL, F_AST | STRERROR, 1);
	close(fd[NEXT][WRITE]);
	setup_redirections(cmd->redirs);
	execute_command(cmd);
}
