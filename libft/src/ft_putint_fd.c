/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:15:53 by aloimusa          #+#    #+#             */
/*   Updated: 2025/06/13 22:15:54 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short int	ft_intlen(int n);

ssize_t	ft_putint_fd(int n, int fd)
{
	char		array[12];
	short int	i;
	short int	len;

	len = ft_intlen(n);
	i = len;
	array[i] = '\0';
	if (n < 0)
	{
		if (n == INT_MIN)
			return (write(fd, "-2147483648", 11));
		array[0] = '-';
		n = -n;
	}
	while (n % 10 != n)
	{
		array[--i] = (n % 10) + '0';
		n = (n - (n % 10)) / 10;
	}
	array[--i] = n + '0';
	return (write(fd, &array, len));
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
