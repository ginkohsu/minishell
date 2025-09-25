/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:15:22 by jinxu             #+#    #+#             */
/*   Updated: 2025/08/12 02:05:15 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_hex(unsigned int n, int is_upper, int *err)
{
	const char	*print_base;
	char		res[9];
	int			i;
	int			len;

	if (n == 0)
	{
		if (write(1, "0", 1) < 0)
			*err = 1;
		return (1);
	}
	print_base = "0123456789abcdef";
	if (is_upper == 1)
		print_base = "0123456789ABCDEF";
	i = 0;
	while (n > 0)
	{
		res[i++] = print_base[n % 16];
		n = n / 16;
	}
	len = i;
	while (--i >= 0)
		if (write(1, &res[i], 1) < 0)
			*err = 1;
	return (len);
}
