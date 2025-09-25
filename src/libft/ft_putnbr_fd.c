/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:51:45 by jinxu             #+#    #+#             */
/*   Updated: 2025/04/21 19:15:30 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	numstr[11];
	int		i;

	nbr = n;
	i = 0;
	if (nbr == 0)
	{
		write (fd, "0", 1);
		return ;
	}
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = -nbr;
	}
	while (nbr != 0)
	{
		numstr[i++] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	while (i > 0)
		write (fd, &numstr[--i], 1);
}
