/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 03:54:29 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/22 03:54:30 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*get_path(char **prog);
static char	*get_path2(char **prog, char *ptr);

// execute command (builtin or external)
void	execute_command(t_command *cmd)
{
	char	*path;

	if (is_builtin(cmd->argv[0]))
	{
		if (ft_strcmp("echo", cmd->argv[0]) == 0)
			exit(ft_echo(cmd->argv, 0));
		if (ft_strcmp("cd", cmd->argv[0]) == 0)
			exit(ft_cd(cmd->argv, 0));
		if (ft_strcmp("pwd", cmd->argv[0]) == 0)
			exit(ft_pwd(cmd->argv, 0));
		if (ft_strcmp("export", cmd->argv[0]) == 0)
			exit(ft_export(cmd->argv, 0));
		if (ft_strcmp("unset", cmd->argv[0]) == 0)
			exit(ft_unset(cmd->argv, 0));
		if (ft_strcmp("env", cmd->argv[0]) == 0)
			exit(ft_env(cmd->argv, 0));
		if (ft_strcmp("exit", cmd->argv[0]) == 0)
			exit(ft_exit(cmd->argv, 0));
	}
	path = get_path(cmd->argv);
	if (!path)
		exittool(ERR_CMD_NOT_FOUND, cmd->argv[0], P_OBJ | F_AST | F_ENV, 127);
	if (execve(path, cmd->argv, fetchenv(NULL)) == -1)
		exittool(ERR_EXECVE, path, F_OBJ | F_AST | F_ENV | STRERR, 1);
}

// execute builtin in parent process
int	parent_builtin(t_command *cmd)
{
	if (ft_strcmp("echo", cmd->argv[0]) == 0)
		return (ft_echo(cmd->argv, PPROC));
	else if (ft_strcmp("cd", cmd->argv[0]) == 0)
		return (ft_cd(cmd->argv, PPROC));
	else if (ft_strcmp("pwd", cmd->argv[0]) == 0)
		return (ft_pwd(cmd->argv, PPROC));
	else if (ft_strcmp("export", cmd->argv[0]) == 0)
		return (ft_export(cmd->argv, PPROC));
	else if (ft_strcmp("unset", cmd->argv[0]) == 0)
		return (ft_unset(cmd->argv, PPROC));
	else if (ft_strcmp("env", cmd->argv[0]) == 0)
		return (ft_env(cmd->argv, PPROC));
	else if (ft_strcmp("exit", cmd->argv[0]) == 0)
		return (ft_exit(cmd->argv, PPROC));
	return (0);
}

static char	*get_path(char **prog)
{
	char	*ptr;
	char	**env;
	DIR		*dir;

	if (!prog[0] || prog[0][0] == '\0')
		return (NULL);
	if (is_path(prog[0]))
	{
		dir = opendir(prog[0]);
		if (dir)
		{
			closedir(dir);
			exittool(ERR_IS_DIR, prog[0], P_OBJ | F_AST | F_ENV, 126);
		}
		if (access(prog[0], X_OK) == 0)
			return (ft_strdup(prog[0]));
		exittool(NULL, prog[0], F_AST | F_ENV | EXEC_FAIL, 0);
	}
	ptr = NULL;
	env = fetchenv("PATH");
	if (env)
		ptr = env[0];
	if (!ptr || ft_strlen(ptr) < 5 || ft_strncmp(ptr, "PATH=", 5) != 0)
		exittool(NULL, prog[0], F_AST | F_ENV | EXEC_FAIL, 0);
	return (get_path2(prog, ptr));
}

static char	*get_path2(char **prog, char *ptr)
{
	int		i;
	char	**array;

	array = ft_split(ptr + 5, ':');
	if (!array)
		exittool(ERR_MALLOC, NULL, F_AST | F_ENV | STRERR, 2);
	i = -1;
	while (array[++i])
	{
		if (!array[i][0])
			continue ;
		ptr = ft_strapp(ft_strjoin(array[i], "/"), prog[0]);
		if (access(ptr, X_OK) == 0)
			break ;
		free(ptr);
		ptr = NULL;
	}
	free_array(array);
	return (ptr);
}
