/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:16:11 by aloimusa          #+#    #+#             */
/*   Updated: 2025/06/13 22:16:12 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short int	ft_intlen(unsigned int n);

ssize_t	ft_putuint_fd(unsigned int n, int fd)
{
	char		array[11];
	short int	i;
	short int	len;

	len = ft_intlen(n);
	i = len;
	array[i] = '\0';
	while (n % 10 != n)
	{
		array[--i] = (n % 10) + '0';
		n = (n - (n % 10)) / 10;
	}
	array[--i] = n + '0';
	return (write(fd, &array, len));
}

static short int	ft_intlen(unsigned int n)
{
	short int	i;

	i = 1;
	while (n % 10 != n)
	{
		n = (n - (n % 10)) / 10;
		i++;
	}
	return (i);
}
