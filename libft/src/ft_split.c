/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:35:07 by aloimusa          #+#    #+#             */
/*   Updated: 2025/04/29 13:25:50 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_split_array(char **array, const char *s, char c);
static void	freeall(char **array, size_t k);

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
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			word++;
		while (s[i] && s[i] != c)
			i++;
	}
	array = malloc((word + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (ft_split_array(array, s, c))
		return (array);
	return (NULL);
}

static int	ft_split_array(char **array, const char *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			array[count] = ft_strndup(&s[start], i - start);
			if (!array[count++])
			{
				freeall(array, count);
				return (0);
			}
		}
	}
	array[count] = NULL;
	return (1);
}

static void	freeall(char **array, size_t k)
{
	while (k-- != 0)
		free(array[k]);
	free(array);
}
