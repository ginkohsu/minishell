/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:41:59 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/26 21:18:28 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_argument_to_cmd(t_command *cmd, char *arg)
{
	int		count;
	char	**new_argv;

	if (!arg)
		return (PARSE_MALLOC_ERROR);
	count = 0;
	if (cmd->argv)
	{
		while (cmd->argv[count])
			count++;
	}
	new_argv = malloc((count + 2) * sizeof(char *));
	if (!new_argv)
		return (PARSE_MALLOC_ERROR);
	if (cmd->argv)
	{
		ft_memcpy(new_argv, cmd->argv, count * sizeof(char *));
		free(cmd->argv);
	}
	new_argv[count] = arg;
	new_argv[count + 1] = NULL;
	cmd->argv = new_argv;
	return (PARSE_SUCCESS);
}
