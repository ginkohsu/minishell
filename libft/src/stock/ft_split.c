/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 04:22:42 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 04:40:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_split2(char **array, const char *s, char c)
{
	size_t	start;
	size_t	i;
	size_t	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			array[word] = ft_strndup(&s[start], i - start);
			if (!array[word++])
			{
				free_array(array);
				return ;
			}
		}
	}
	array[word] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	word;

	if (!s)
		return (NULL);
	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			word++;
		while (s[i] && s[i] != c)
			i++;
	}
	array = malloc((word + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	ft_split2(array, s, c);
	return (array);
}
