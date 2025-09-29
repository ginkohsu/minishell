/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:16:48 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/25 14:44:48 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *extract_word(char **input)
{
	char	*start;
	int		len;
	char	*word;

	if (!input || !*input || !**input)
		return (NULL);
	start = *input;
	len = 0;
	while (**input && !ft_isspace(**input) && !is_special_char(**input))
	{
		(*input)++;
		len++;
	}
	if (len == 0)
		return (NULL);
	word = malloc (len + 1);
	if (!word)
		return (NULL); //??????????????ERROR HANDLING
	ft_strlcpy(word, start, (size_t)(len + 1));
	return (word);
}
