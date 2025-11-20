/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:48:34 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/20 11:20:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char **env)
{
	char	**ptr;
	char	*str;
	int		lvl;

	setup_signal_handlers();
	initenv(env);
	ptr = fetchenv("SHLVL");
	if (!ptr || !ptr[0])
		return ;
	lvl = ft_atoi(ptr[0] + 6);
	str = ft_strprep("SHLVL=", ft_itoa(++lvl));
	if (str)
		if (!addenv(str))
			free(str);
}

static char	*read_line(void)
{
	char	*line;
	char	*tmp;

	g_signal = 1;
	line = NULL;
	if (isatty(STDIN_FILENO))
	{
		line = readline("minishell$ ");
		if (!line)
			write(1, "exit\n", 5);
	}
	else
	{
		tmp = get_next_line(STDIN_FILENO);
		if (tmp)
		{
			line = ft_strtrim(tmp, "\n");
			free(tmp);
		}
	}
	return (line);
}

void	process_line(char *line, bool tty)
{
	t_ast	*tree;

	if (tty)
	{
		if (!*line)
		{
			free(line);
			return ;
		}
		add_history(line);
	}
	tree = parse(line);
	if (tty)
		free(line);
	if (tree)
		execute_ast(tree);
	g_signal = 1;
}

bool	interactive_mode(void)
{
	char	*line;

	line = read_line();
	if (!line)
		return (false);
	process_line(line, true);
	if (g_signal == 0)
	{
		if (!set_exit(130))
			ft_fprintf(2, "malloc failed\n");
	}
	return (true);
}
