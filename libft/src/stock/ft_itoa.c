/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 04:48:52 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 04:53:55 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short int	ft_intlen(int n)
{
	short int	i;

	i = 1;
	if (n < 0)
	{
		if (n == INT_MIN)
			return (11);
		n = -n;
		i++;
	}
	while (n % 10 != n)
	{
		n = (n - (n % 10)) / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	short	i;
	char	*str;

	i = ft_intlen(n);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		if (n == INT_MIN)
		{
			(void)ft_strlcpy(str, "-2147483648", 12);
			return (str);
		}
		n = -n;
		str[0] = '-';
	}
	str[i] = '\0';
	while (n % 10 != n)
	{
		str[--i] = (n % 10) + '0';
		n = (n - (n % 10)) / 10;
	}
	str[--i] = n + '0';
	return (str);
}
