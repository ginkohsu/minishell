/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:38:32 by jinxu             #+#    #+#             */
/*   Updated: 2025/04/22 18:26:46 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

static int		word_count(char const *s, char c);
static void		ft_free(char **arr);
static size_t	get_next_word(const char *s, char c, unsigned int *start);

char	**ft_split(char const *s, char c)
{
	char			**strs;
	unsigned int	num_strs;
	unsigned int	i;
	unsigned int	start;
	size_t			len;

	if (!s)
		return (NULL);
	num_strs = word_count(s, c);
	strs = malloc ((num_strs + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	start = 0;
	while (i < num_strs)
	{
		len = get_next_word(s, c, &start);
		strs[i] = ft_substr(s, start, len);
		if (!strs[i])
			return (ft_free(strs), NULL);
		start += len;
		i++;
	}
	strs[i] = 0;
	return (strs);
}

static int	word_count(char const *s, char c)
{
	int	count;
	int	in_word;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (! in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static size_t	get_next_word(const char *s, char c, unsigned int *start)
{
	size_t	len;

	len = 0;
	while (s[*start] == c)
		(*start)++;
	while ((s[*start + len] != c) && (s[*start + len]))
		len++;
	return (len);
}

static void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free (arr[i]);
		i++;
	}
	free (arr);
}

/* free(NULL)
It is good practice to not bother checking 
for NULL before calling free.
Checking just adds unnecessary clutter to your code,
and free(NULL) is guaranteed to be safe.
From section 7.20.3.2/2 of the C99 standard:

The free function causes the space pointed to
by ptr to be deallocated, that is,
made available for further allocation.
If ptr is a null pointer, no action occurs.
*/
