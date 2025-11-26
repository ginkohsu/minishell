/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:16:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/25 12:16:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		if (!set_exit(130))
			write(STDERR_FILENO, "malloc failed\n", 14);
	}
}

int	check_signal(void)
{
	extern int	rl_done;

	if (g_signal == SIGINT)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

void	in_session(bool active, struct sigaction *old_sa)
{
	struct sigaction	sa;
	extern int			(*rl_event_hook)(void);

	if (active)
	{
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_handler = heredoc_sighandler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, old_sa);
		rl_event_hook = check_signal;
		return ;
	}
	if (g_signal == SIGINT)
		g_signal = 0;
	sigaction(SIGINT, old_sa, NULL);
	rl_event_hook = NULL;
}
