/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:06:13 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/20 11:20:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_exit_code(void)
{
	char	*exit_str;
	int		code;

	exit_str = getenvstr("?");
	code = ft_atoi(exit_str);
	free(exit_str);
	return (code);
}

int	main(int ac, char **av, char **env)
{
	int		exit_code;
	bool	tty;

	tty = init_shell(env);
	g_signal = 1;
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		process_line(av[2], false);
	else
		while (interactive_mode(tty))
			g_signal = 1;
	exit_code = get_exit_code();
	clear_history();
	initenv(NULL);
	return (exit_code);
}
