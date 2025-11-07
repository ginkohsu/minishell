/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:00:26 by aloimusa          #+#    #+#             */
/*   Updated: 2025/04/29 13:41:35 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

int	ft_atoi(const char *str)
{
	short		i;
	short		pm;
	long long	integer;
	int			ans;

	if (!str)
		return (0);
	i = 0;
	integer = 0;
	pm = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pm *= -1;
	while (str[i] >= '0' && str[i] <= '9')
		integer = integer * 10 + (str[i++] - '0');
	if (integer > INT_MAX || integer < INT_MIN)
		errno = ERANGE;
	ans = (int)integer;
	return (ans *= pm);
}
