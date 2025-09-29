/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:25:29 by aloimusa          #+#    #+#             */
/*   Updated: 2025/04/28 17:55:35 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char c, char const *charset);

char	*ft_strtrim(char const *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*cpy;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (ft_ischarset(s1[start], set) && s1[start])
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_ischarset(s1[end - 1], set))
		end--;
	cpy = malloc((end - start + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	(void)ft_strlcpy(cpy, &s1[start], end - start + 1);
	return (cpy);
}

static int	ft_ischarset(char c, char const *charset)
{
	int	i;

	i = 0;
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}
