/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:06:13 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/18 16:10:41 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<signal.h>

void sig_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(void)
{
	char	*line;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT,SIG_IGN);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line)
			add_history(line);
		printf("You entered: %s\n", line);
		free(line);
	}
	return 0;
}
