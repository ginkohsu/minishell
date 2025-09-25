/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:37:50 by jinxu             #+#    #+#             */
/*   Updated: 2025/08/12 02:06:25 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str(char *str, int *err)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		if (write(1, "(null)", 6) < 0)
			*err = 1;
		i += 6;
	}
	else
	{
		i += ft_strlen(str);
		if (write(1, str, i) < 0)
			*err = 1;
	}
	return (i);
}
