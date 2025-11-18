/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:06:13 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/04 21:09:53 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 1;

void	sig_handler(int signum)
{
	(void)signum;
	g_signal = 0;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	process_input(char *line)
{
	t_ast	*tree;

	if (!*line)
		return ;
	add_history(line);
	tree = parse(line);
	if (tree)
		execute_ast(tree);
	free(line);
}

static bool	running(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		write(1, "exit\n", 5);
		return (false);
	}
	if (g_signal == 0)
	{
		if (!set_exit(130))
			ft_fprintf(2, "malloc failed\n");
		return (false);
	}
	g_signal = 1;
	process_input(line);
	return (true);
}

int	main(int ac, char **av, char **env)
{
	char	*exit_str;
	int		code;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	initenv(env);
	while (running())
		;
	exit_str = getenvstr("?");
	code = ft_atoi(exit_str);
	free(exit_str);
	clear_history();
	initenv(NULL);
	return (code);
}
