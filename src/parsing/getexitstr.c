/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getexitstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:20:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/02 22:20:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getexitstr(void)
{
	char	**env;

	env = fetchenv("?");
	if (env && env[0])
		return (ft_strdup(env[0] + 2));
	return (ft_strdup("0"));
}
