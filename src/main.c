/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:06:13 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/22 20:27:40 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		token_count;
	t_token	*tokens;

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
		tokens = tokenize(line, &token_count);
		
		print_tokens_debug(tokens, token_count); //for testing

		free_tokens(tokens, token_count);
		
		free(line);
	}
	return 0;
}
