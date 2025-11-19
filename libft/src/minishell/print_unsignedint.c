/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsignedint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:48:59 by jinxu             #+#    #+#             */
/*   Updated: 2025/08/12 02:06:43 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_unsignedint(unsigned int nbr, int	*err)
{
	int				i;
	char			str[10];
	int				len;

	if (nbr == 0)
	{
		if (write (1, "0", 1) < 0)
			*err = 1;
		return (1);
	}
	i = 0;
	while (nbr > 0)
	{
		str[i++] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	len = i;
	while (--i >= 0)
	{
		if (write(1, &str[i], 1) < 0)
			*err = 1;
	}
	return (len);
}
