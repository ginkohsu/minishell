/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:57:14 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/09 18:58:45 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[++i])
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	return (1);
}

int	ft_env(char **av)
{
	char	**array;
	int		i;

	(void)av;
	array = fetchenv(NULL);
	if (!array)
		return (1);
	i = -1;
	while (array[++i])
		write(1, array[i], ft_strlen(array[i]));
	return (0);
}

int	ft_export(char **av)
{
	int		i;
	char	**array;

	if (!av[1])
	{
		i = -1;
		array = get_sorted_env();
		while (array[++i])
			ft_printf("declare -x %s\n", array[i]);
		return (0);
	}
	i = 0;
	while (av[++i])
	{
		if (is_valid_identifier(av[i]))
			addenv(av[i]);
		else
			ft_fprintf(2, "export: '%s': not a valid identifier", av[i]);
	}
	return (0);
}

int	ft_unset(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (is_valid_identifier(av[i]))
			rmenv(av[i]);
		else
			ft_fprintf(2, "unset: '%s': not a valid identifier", av[i]);
	}
	return (0);
}
