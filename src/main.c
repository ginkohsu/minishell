/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:06:13 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/19 20:46:43 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*tmp;

	if (isatty(STDIN_FILENO))
		line = readline("minishell$ ");
	else
	{
		tmp = get_next_line(STDIN_FILENO);
		if (!tmp)
			return (false);
		line = ft_strtrim(tmp, "\n");
		free(tmp);
	}
	if (!line)
	{
		write(1, "exit\n", 5);
		return (false);
	}
	g_signal = 1;
	process_input(line);
	return (true);
}

static void	shlvlup(void)
{
	char	**ptr;
	char	*str;
	int		lvl;

	ptr = fetchenv("SHLVL");
	if (!ptr || !ptr[0])
		return ;
	lvl = ft_atoi(ptr[0] + 6);
	str = ft_strprep("SHLVL=", ft_itoa(++lvl));
	if (str)
		if (!addenv(str))
			free(str);
}

static int	handle_c_flag(char *cmd)
{
	t_ast	*tree;
	char	*exit_str;
	int		code;

	tree = parse(cmd);
	if (tree)
		execute_ast(tree);
	exit_str = getenvstr("?");
	code = ft_atoi(exit_str);
	free(exit_str);
	clear_history();
	initenv(NULL);
	return (code);
}

int	main(int ac, char **av, char **env)
{
	char	*exit_str;
	int		code;

	setup_signal_handlers();
	initenv(env);
	shlvlup();
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		return (handle_c_flag(av[2]));
	while (running())
	{
		if (g_signal == 0)
		{
			if (!set_exit(130))
				ft_fprintf(2, "malloc failed\n");
			break ;
		}
	}
	exit_str = getenvstr("?");
	code = ft_atoi(exit_str);
	free(exit_str);
	clear_history();
	initenv(NULL);
	return (code);
}
