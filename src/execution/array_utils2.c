/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:16:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/13 17:16:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// find position of string in array with length limit (like strnchr)
int	arrstrn(char **arr, char *str, int n)
{
	int	i;

	if (!arr || !str)
		return (-1);
	i = -1;
	while (arr[++i])
		if (ft_strncmp(arr[i], str, n) == 0)
			return (i);
	return (-1);
}

// sort array of strings in place (bubble sort)
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
