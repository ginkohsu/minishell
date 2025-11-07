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

void	sig_handler(int signum)
{
	(void)signum;
	printf("\n");
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

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*exit_status;
	int		code;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	initenv(env);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		process_input(line);
	}
	exit_status = getenvstr("?");
	code = ft_atoi(exit_status);
	free(exit_status);
	clear_history();
	initenv(NULL);
	return (code);
}
