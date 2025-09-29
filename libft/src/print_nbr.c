/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:42:53 by jinxu             #+#    #+#             */
/*   Updated: 2025/08/12 02:05:45 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	zero_case(long nbr, int *err);

int	print_nbr(long nbr, int *err)
{
	char	numstr[11];
	int		i;
	int		ct;

	i = 0;
	ct = 0;
	if (zero_case(nbr, err))
		return (1);
	if (nbr < 0)
	{
		if (write(1, "-", 1) < 0)
			*err = 1;
		nbr = -nbr;
		ct += 1;
	}
	while (nbr != 0)
	{
		numstr[i++] = (nbr % 10) + '0';
		nbr = nbr / 10;
		ct++;
	}
	while (i > 0)
		if (write (1, &numstr[--i], 1) < 0)
			*err = 1;
	return (ct);
}

static int	zero_case(long nbr, int *err)
{
	if (nbr == 0)
	{
		if (write(1, "0", 1) < 0)
			*err = 1;
		return (1);
	}
	return (0);
}
