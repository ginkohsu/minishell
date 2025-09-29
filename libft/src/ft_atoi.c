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

int	ft_atoi(const char *str)
{
	int	i;
	int	integer;
	int	pm;

	if (!ft_strncmp(str, "-2147483648", 12))
		return (INT_MIN);
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
	return (integer *= pm);
}
