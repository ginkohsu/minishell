/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 20:05:36 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/22 20:07:21 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens, int count)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (i < count)
	{
		if (tokens[i].value) 
			free(tokens[i].value);
		i++;
	}
	free(tokens);
}
