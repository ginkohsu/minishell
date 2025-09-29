/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:41:08 by aloimusa          #+#    #+#             */
/*   Updated: 2025/04/28 18:26:47 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short int	ft_intlen(int n);

char	*ft_itoa(int n)
{
	short int	i;
	char		*str;

	i = ft_intlen(n);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (n < 0)
	{
		if (n == INT_MIN)
		{
			ft_memmove(str, "-2147483648", 11);
			return (str);
		}
		str[0] = '-';
		n = -n;
	}
	while (n % 10 != n)
	{
		str[--i] = (n % 10) + '0';
		n = (n - (n % 10)) / 10;
	}
	str[--i] = n + '0';
	return (str);
}

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
