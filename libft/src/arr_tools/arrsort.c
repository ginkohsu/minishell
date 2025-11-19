/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 06:07:37 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 06:07:55 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	arrsort(char **arr)
{
	int	i;
	int	j;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i] && arr[i + 1])
	{
		j = i;
		while (arr[++j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				arr[i] = (char *)((uintptr_t)arr[i] ^ (uintptr_t)arr[j]);
				arr[j] = (char *)((uintptr_t)arr[j] ^ (uintptr_t)arr[i]);
				arr[i] = (char *)((uintptr_t)arr[i] ^ (uintptr_t)arr[j]);
			}
		}
	}
}
