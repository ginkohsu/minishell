/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:31:54 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/01 17:33:37 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	update_cwd(char *s, int f)
{
	char	**env;
	char	*tmp;

	if (chdir(s) == -1)
		return (exittool(ERR_CD_PATH, s, P_OBJ | STRERR | F_AST | F_ENV | f,
				1));
	env = fetchenv("PWD");
	if (env)
	{
		tmp = ft_strprep("OLDPWD=", ft_strdup(ft_strchr(env[0], '=') + 1));
		if (addenv(tmp) == -1)
			return (exittool(ERR_ENV_CORRUPT, tmp, F_OBJ | F_AST | F_ENV | f,
					1));
		free(tmp);
	}
	s = getcwd(NULL, 0);
	if (!s)
		return (exittool(ERR_CD_CWD, NULL, STRERR | F_AST | F_ENV | f, 1));
	tmp = ft_strprep("PWD=", s);
	if (addenv(tmp) == -1)
		return (exittool(ERR_ENV_CORRUPT, tmp, F_OBJ | F_AST | F_ENV | f, 1));
	return (exittool(NULL, tmp, F_OBJ | F_AST | F_ENV | f, 0));
}

// change directory builtin
int	ft_cd(char **av, int f)
{
	char	**env;
	char	*path;

	if (av[1] && av[2])
		return (exittool(ERR_CD_MANY_ARGS, NULL, F_AST | F_ENV | f, 1));
	if (!av[1])
	{
		env = fetchenv("HOME");
		if (!env)
			return (exittool(ERR_CD_HOME_UNSET, NULL, F_AST | F_ENV | f, 1));
		return (update_cwd(ft_strchr(env[0], '=') + 1, f));
	}
	else if (ft_strncmp(av[1], "-", 2) == 0)
	{
		env = fetchenv("OLDPWD");
		if (!env)
			return (exittool(ERR_CD_OLDPWD_UNSET, NULL, F_AST | F_ENV | f, 1));
		path = ft_strchr(env[0], '=') + 1;
		ft_printf("%s\n", path);
		return (update_cwd(path, f));
	}
	else
		return (update_cwd(av[1], f));
}

// exit shell with status code
int	ft_exit(char **av, int f)
{
	int	i;

	write(1, "exit\n", 5);
	if (!av[1])
		return (exittool(NULL, NULL, F_AST | F_ENV | TRUE_EXIT | f, 0));
	if (av[1] && av[2])
		return (exittool(ERR_EXIT_MANY_ARGS, NULL, F_AST | f, 1));
	i = 0;
	if (av[1][i] == '+' || av[1][i] == '-')
		i++;
	while (av[1][i] && !ft_isdigit(av[1][i++]))
		return (exittool(ERR_EXIT_NUMERIC, av[1],
				P_OBJ | F_AST | F_ENV | TRUE_EXIT | f, 2));
	errno = 0;
	i = ft_atoi(av[1]);
	if (errno == ERANGE)
		return (exittool(ERR_EXIT_NUMERIC, av[1],
				P_OBJ | F_AST | F_ENV | TRUE_EXIT | f, 2));
	return (exittool(NULL, NULL, F_AST | F_ENV | TRUE_EXIT | f,
			(unsigned char)i));
}

// print arguments to stdout
int	ft_echo(char **av, int f)
{
	int		i;
	int		s;
	bool	nl;

	nl = true;
	s = 0;
	while (av[++s] && av[s][0] == '-')
	{
		i = 0;
		while (av[s][++i] == 'n')
			;
		if (i > 1 && !av[s][i])
			nl = false;
		else
			break ;
	}
	while (av[s++])
		if (write(1, av[s - 1], ft_strlen(av[s - 1])) != -1 && av[s])
			write(1, " ", 1);
	if (nl)
		write(1, "\n", 1);
	return (exittool(NULL, NULL, F_AST | F_ENV | f, 0));
}

// print working directory
int	ft_pwd(char **av, int f)
{
	char	**array;
	char	*path;

	(void)av;
	array = fetchenv("PWD");
	if (!array)
		return (exittool(NULL, NULL, F_AST | F_ENV | f, 1));
	path = ft_strchr(array[0], '=') + 1;
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	return (exittool(NULL, NULL, F_AST | F_ENV | f, 0));
}
