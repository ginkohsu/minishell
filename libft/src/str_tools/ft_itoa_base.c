/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 07:50:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 07:50:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short int	ft_numlen_base(unsigned long n, int baselen)
{
	short int	i;

	if (!n)
		return (1);
	i = 0;
	while (n > 0)
	{
		n = n / baselen;
		i++;
	}
	return (i);
}

char	*ft_itoa_base(unsigned long n, char *base)
{
	char		*str;
	short int	i;
	int			baselen;

	if (!base)
		return (NULL);
	baselen = ft_strlen(base);
	if (baselen < 2)
		return (NULL);
	i = ft_numlen_base(n, baselen);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (!n)
	{
		str[0] = base[0];
		return (str);
	}
	while (n > 0)
	{
		str[--i] = base[n % baselen];
		n = n / baselen;
	}
	return (str);
}
