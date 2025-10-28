/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 00:54:02 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/28 00:54:03 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast(t_ast *ast, int depth)
{
	(void)ast;
	(void)depth;
}

char	*expand_vars_dquote(char *src)
{
	return (ft_strdup(src));
}
