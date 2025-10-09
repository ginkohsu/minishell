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

int	ft_cd(char **av)
{
	char	**env;
	char	*entry;

	if (av[1] && av[2])
		ft_error("cd: too many arguments\nbuiltins.c:21\n", NULL, F_AST, 2);
	if (!av[1])
	{
		env = fetchenv("HOME");
		if (!env)
			ft_error("cd: HOME not set\nbuiltins.c:26\n", NULL, F_AST, 1);
		rmenv("PWD");
		entry = ft_strjoin("PWD=", env[0]);
		addenv(entry);
		free(entry);
		return (0);
	}
	if (chdir(av[1]) == -1)
		ft_error("cd: %s: %s\nbuiltins.c:34\n", av[1], STRERROR | P_OBJ | F_AST, 1);
	rmenv("PWD");
	entry = ft_strjoin("PWD=", av[1]);
	addenv(entry);
	free(entry);
	return (0);
}

int	ft_exit(char **av)
{
	int	i;

	write(2, "exit\n", 5);
	if (av[1] && av[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	if (!av[1])
	{
		free_ast_root();
		exit(0);
	}
	i = 0;
	while (av[1][++i])
		if (!ft_isdigit(av[1][i - 1]))
			ft_error("exit: %s: numeric argument required\nbuiltins.c:60\n", av[1], P_OBJ | F_AST, 2);
	free_ast_root();
	exit((unsigned char)ft_atoi(av[1]));
}

int	ft_echo(char **av)
{
	int		i;
	bool	nl;

	if (av[1] && ft_strcmp(av[1], "-n") == 0)
	{
		nl = true;
		i = 1;
	}
	else
	{
		nl = false;
		i = 0;
	}
	while (av[++i])
		if (write(1, av[i], ft_strlen(av[i])) != -1 && av[i + 1])
			write(1, " ", 1);
	if (!nl)
		write(1, "\n", 1);
	return (0);
}

int	ft_pwd(char **av)
{
	char	**array;

	(void)av;
	array = fetchenv("PWD");
	if (!array)
		return (1);
	write(1, array[0], ft_strlen(array[0]));
	return (0);
}
