/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:25:43 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/25 15:47:53 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int	is_env_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || ( c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') || c == '_');
}

char	*handle_env_var(char **input)
{
}


void handle_env_var_char(char **input, t_token *collected_tokens, int *count)
{
}


