/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 00:02:59 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/09 00:33:31 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	return (ft_strcmp(name, "echo") == 0 || ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "pwd") == 0 || ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0 || ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "exit") == 0);
}

void	free_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	count_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		;
	return (i);
}

static void	open_fail(char *file)
{
	if (errno == EPERM || errno == EACCES)
		ft_error("%s: permission denied", file, P_OBJ, 1);
	else if (errno == ENOSPC)
		ft_error("%s: no space left on device", file, P_OBJ, 0);
	else if (errno == ENOENT)
		ft_error("%s: no such file", file, P_OBJ, 126);
	else if (errno == EISDIR)
		ft_error("%s: is a directory", file, P_OBJ, 126);
	else
		ft_error("%s: undefined error opening file", file, P_OBJ, 1);
}

void	ft_error(char *msg, void *obj, int action, unsigned char code)
{
	if (msg && obj && (action & P_OBJ) && (action & STRERROR))
		ft_fprintf(2, msg, obj, strerror(errno));
	else if (msg && (action & STRERROR))
		ft_fprintf(2, msg, strerror(errno));
	else if (msg && obj && (action & P_OBJ))
		ft_fprintf(2, msg, obj);
	else if (msg)
		ft_fprintf(2, msg);
	if (action & F_AST)
		free_ast_root();
	if (action & F_ARRAY)
		free_array((char **)obj);
	if (obj && (action & F_OBJ))
		free(obj);
	if (msg && (action & F_MSG))
		free(msg);
	if (action & STAY)
		return ;
	if (action & OPEN_FAIL)
		open_fail(obj);
	exit(code);
}
