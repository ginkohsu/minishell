/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 07:50:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 07:50:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

long	ft_atol(const char *str)
{
	long long	number;
	short		pm;
	long		l;

	number = 0;
	pm = 1;
	l = 0;
	while (str[l] == ' ' || (str[l] >= '\t' && str[l] <= '\r'))
		l++;
	if (str[l] == '+' || str[l] == '-')
		if (str[l++] == '-')
			pm *= -1;
	while (str[l] >= '0' && str[l] <= '9')
		number = number * 10 + (str[l++] - '0');
	if (number > LONG_MAX || number < LONG_MIN)
		errno = ERANGE;
	l = (long)number;
	return (l *= pm);
}
