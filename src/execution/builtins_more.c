/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 03:54:10 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/22 03:54:11 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// check if string is valid env variable
static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[++i] && str[i] != '=')
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	return (1);
}

// print environment variables
int	ft_env(char **av, int f)
{
	char	**array;
	int		i;

	(void)av;
	array = fetchenv(NULL);
	if (!array)
		return (exittool(NULL, NULL, F_AST | F_ENV | f, 1));
	i = -1;
	while (array[++i])
		if (write(1, array[i], ft_strlen(array[i])) != -1)
			write(1, "\n", 1);
	return (exittool(NULL, NULL, F_AST | F_ENV | f, 0));
}

// export variables to environment
int	ft_export(char **av, int f)
{
	int		i;
	int		status;
	char	**array;

	if (!av[1])
	{
		array = arrdup(fetchenv(NULL));
		if (!array)
			return (exittool(NULL, NULL, F_AST | F_ENV | f, 1));
		arrsort(array);
		i = -1;
		while (array[++i])
			ft_printf("declare -x %s\n", array[i]);
		return (exittool(NULL, array, F_ARR | F_AST | F_ENV | f, 0));
	}
	status = 0;
	i = 0;
	while (av[++i])
	{
		if (!is_valid_identifier(av[i]) && ++status)
			ft_fprintf(2, ERR_EXPORT_INVALID, av[i]);
		else if (addenv(av[i]) == -1)
			return (exittool(ERR_ENV_CORRUPT, NULL, F_AST | F_ENV | f, 1));
	}
	return (exittool(NULL, NULL, F_AST | F_ENV | f, (bool)status));
}

// remove variables from environment
int	ft_unset(char **av, int f)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (is_valid_identifier(av[i]) && rmenv(av[i]) == -1)
			return (exittool(ERR_ENV_CORRUPT, NULL, F_AST | F_ENV | f, 1));
	}
	return (exittool(NULL, NULL, F_AST | F_ENV | f, 0));
}
