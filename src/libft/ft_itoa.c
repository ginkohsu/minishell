/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:56:05 by jinxu             #+#    #+#             */
/*   Updated: 2025/04/27 19:28:42 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static size_t	count_len(long long nbr);

char	*ft_itoa(int n)
{
	char		*str;
	size_t		len;
	size_t		neg;
	long long	nbr;

	neg = 0;
	nbr = (long long)n;
	if (nbr < 0)
	{
		nbr = -nbr;
		neg = 1;
	}
	len = count_len(nbr);
	str = malloc (len + 1 + neg);
	if (!str)
		return (NULL);
	if (neg)
		str[0] = '-';
	str[len + neg] = '\0';
	while (len)
	{
		str[--len + neg] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (str);
}

static size_t	count_len(long long nbr)
{
	size_t	count;

	count = 0;
	if (nbr == 0)
		count = 1;
	while (nbr > 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}
