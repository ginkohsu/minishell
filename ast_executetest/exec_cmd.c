/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:40:28 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/09 13:40:28 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*get_path(char **prog);
static char	*get_path2(char **prog, char *ptr);

void	execute_command(t_command *cmd)
{
	char	*path;

	if (is_builtin(cmd->argv[0]))
	{
		if (ft_strcmp("echo", cmd->argv[0]) == 0)
			exit(ft_echo(cmd->argv));
		if (ft_strcmp("cd", cmd->argv[0]) == 0)
			exit(ft_cd(cmd->argv));
		if (ft_strcmp("pwd", cmd->argv[0]) == 0)
			exit(ft_pwd(cmd->argv));
		if (ft_strcmp("export", cmd->argv[0]) == 0)
			exit(ft_export(cmd->argv));
		if (ft_strcmp("unset", cmd->argv[0]) == 0)
			exit(ft_unset(cmd->argv));
		if (ft_strcmp("env", cmd->argv[0]) == 0)
			exit(ft_env(cmd->argv));
		if (ft_strcmp("exit", cmd->argv[0]) == 0)
			exit(ft_exit(cmd->argv));
	}
	path = get_path(cmd->argv);
	if (!path)
		ft_error("%s: command not found", cmd->argv[0], P_OBJ | F_AST, 127);
	if (execve(path, cmd->argv, fetchenv(NULL)) == -1)
		ft_error("execve", path, F_OBJ | F_AST | STRERROR, 1);
}

static char	*get_path(char **prog)
{
	char	*ptr;
	char	**env;

	if (access(prog[0], X_OK) == 0)
		return (ft_strdup(prog[0]));
	env = fetchenv("PATH");
	if (!env)
		ptr = NULL;
	else
		ptr = env[0];
	if (!ptr || ft_strncmp(prog[0], "./", 2) == 0)
	{
		ptr = ft_strdup(prog[0]);
		free_array(prog);
		if (!ptr)
			ft_error("malloc", NULL, F_AST | STRERROR, 2);
		if (errno == ENOENT)
			ft_error("%s: no such file or directory", ptr,
				P_OBJ | F_OBJ | F_AST, 127);
		else if (errno == EPERM || errno == EACCES)
			ft_error("%s: permission denied", ptr, P_OBJ | F_OBJ | F_AST, 126);
		else
			ft_error("%s: not executable", ptr, P_OBJ | F_OBJ | F_AST, 126);
	}
	return (get_path2(prog, ptr));
}

static char	*get_path2(char **prog, char *ptr)
{
	int		i;
	char	**array;

	array = ft_split(ptr + 5, ':');
	if (!array)
		ft_error("malloc", NULL, F_AST | STRERROR, 2);
	i = -1;
	while (array[++i])
	{
		ptr = ft_strapp(ft_strjoin(array[i], "/"), prog[0]);
		if (access(ptr, X_OK) == 0)
			break ;
		free(ptr);
		ptr = NULL;
	}
	free_array(array);
	return (ptr);
}
int	execute_parent_builtin(t_command *cmd)
{
	if (ft_strcmp("echo", cmd->argv[0]) == 0)
		return (ft_echo(cmd->argv));
	else if (ft_strcmp("cd", cmd->argv[0]) == 0)
		return (ft_cd(cmd->argv));
	else if (ft_strcmp("pwd", cmd->argv[0]) == 0)
		return (ft_pwd(cmd->argv));
	else if (ft_strcmp("export", cmd->argv[0]) == 0)
		return (ft_export(cmd->argv));
	else if (ft_strcmp("unset", cmd->argv[0]) == 0)
		return (ft_unset(cmd->argv));
	else if (ft_strcmp("env", cmd->argv[0]) == 0)
		return (ft_env(cmd->argv));
	else if (ft_strcmp("exit", cmd->argv[0]) == 0)
		return (ft_exit(cmd->argv));
	return (0);
}
