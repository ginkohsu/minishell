/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 07:50:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 07:50:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

long long	ft_atoll(const char *str)
{
	long long	number;
	short		pm;
	long long	ll;

	number = 0;
	pm = 1;
	ll = 0;
	while (str[ll] == ' ' || (str[ll] >= '\t' && str[ll] <= '\r'))
		ll++;
	if (str[ll] == '+' || str[ll] == '-')
		if (str[ll++] == '-')
			pm *= -1;
	while (str[ll] >= '0' && str[ll] <= '9')
		number = number * 10 + (str[ll++] - '0');
	ll = (long long)number;
	return (ll *= pm);
}
