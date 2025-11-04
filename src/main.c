/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:06:13 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/03 01:07:01 by jinxu            ###   ########.fr       */
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

static void	cleanup_and_exit(void)
{
	clear_history();
	initenv(NULL);
}

static void	process_input(char *line)
{
	t_ast	*tree;

	if (!*line)
		return ;
	add_history(line);
	tree = parse(line);
	if (tree)
	{
		execute_ast(tree);
		free_ast(tree);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
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
			cleanup_and_exit();
			break ;
		}
		process_input(line);
		free(line);
	}
	line = getenvstr("?");
	code = ft_atoi(line);
	free(line);
	initenv(NULL);
	return (code);
}
