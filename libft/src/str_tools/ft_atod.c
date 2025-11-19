/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 07:50:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 07:50:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*parse_fraction(double *num, const char *s)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] && ft_isdigit(s[i]))
		*num = *num * 10 + (s[i++] - '0');
	ptr = (char *)&s[i];
	while (i-- > 0)
		*num = *num / 10;
	return (ptr);
}

double	ft_atod(const char *s, char **endptr)
{
	int		i;
	double	num;
	short	sign;

	i = 0;
	num = 0.0;
	sign = 1;
	*endptr = (char *)s;
	if (!s)
		return (0.0);
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			sign = -1;
	while (s[i] && ft_isdigit(s[i]))
		num = num * 10 + (s[i++] - '0');
	if (s[i] == '.')
	{
		if (ft_isdigit(s[i + 1]))
			*endptr = parse_fraction(&num, &s[i + 1]);
		else
			*endptr = (char *)&s[i];
	}
	else
		*endptr = (char *)&s[i];
	return (num * sign);
}
