/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 03:54:34 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/22 03:54:35 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// check if command is builtin
int	is_builtin(char *name)
{
	if (!name)
		return (0);
	return (ft_strcmp(name, "echo") == 0 || ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "pwd") == 0 || ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0 || ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "exit") == 0);
}

// free null-terminated string array
void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	array = NULL;
}

// recursively free ast and its contents
void	free_ast(t_ast *ast)
{
	t_redir	*curr;
	t_redir	*next;

	if (!ast)
		return ;
	if (ast->type == CMD)
	{
		if (ast->cmd.argv)
			free_array(ast->cmd.argv);
		curr = ast->cmd.redirs;
		while (curr)
		{
			next = curr->next;
			free(curr->filename);
			free(curr);
			curr = next;
		}
	}
	else if (ast->type == PIPE)
	{
		free_ast(ast->s_pipe.left);
		free_ast(ast->s_pipe.right);
	}
	free(ast);
}

// safely close a file descriptor (pass by reference)
void	safe_close(int *fd)
{
	if (fd && *fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}
