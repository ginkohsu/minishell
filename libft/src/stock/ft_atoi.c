/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 04:44:05 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 04:48:25 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

int	ft_atoi(const char *str)
{
	long long	number;
	short		pm;
	int			i;

	number = 0;
	pm = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pm *= -1;
	while (str[i] >= '0' && str[i] <= '9')
		number = number * 10 + (str[i++] - '0');
	if (number > INT_MAX || number < INT_MIN)
		errno = ERANGE;
	i = (int)number;
	return (i *= pm);
}
