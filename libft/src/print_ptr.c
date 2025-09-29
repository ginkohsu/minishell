/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:19:04 by jinxu             #+#    #+#             */
/*   Updated: 2025/08/12 02:06:08 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_ptr(uintptr_t ptr, int *err)
{
	char	*hex;
	char	buffer[16];
	int		i;
	int		len;

	hex = "0123456789abcdef";
	if (ptr == 0)
	{
		if (write (1, "(nil)", 5) < 0)
			*err = 1;
		return (5);
	}
	if (write(1, "0x", 2) < 0)
		*err = 1;
	i = 0;
	while (ptr > 0)
	{
		buffer[i++] = hex[ptr % 16];
		ptr = ptr / 16;
	}
	len = i + 2;
	while (--i >= 0)
		if (write (1, &buffer[i], 1) < 0)
			*err = 1;
	return (len);
}
