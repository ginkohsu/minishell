/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exittool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:00:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/21 22:00:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	open_fail(char *file)
{
	if (errno == EPERM || errno == EACCES)
		exittool(ERR_PERM_DENIED, file, P_OBJ, 1);
	else if (errno == ENOSPC)
		exittool(ERR_NO_SPACE, file, P_OBJ, 0);
	else if (errno == ENOENT)
		exittool(ERR_NO_FILE, file, P_OBJ, 1);
	else if (errno == EISDIR)
		exittool(ERR_IS_DIR, file, P_OBJ, 1);
	else
		exittool(ERR_OPEN_UNDEF, file, P_OBJ, 1);
}

static void	exec_fail(char *file)
{
	if (errno == ENOENT)
		exittool(ERR_NO_SUCH_FILE, file, P_OBJ | F_AST | F_ENV, 127);
	else if (errno == EISDIR)
		exittool(ERR_IS_DIR, file, P_OBJ | F_AST | F_ENV, 126);
	else if (errno == EPERM || errno == EACCES)
		exittool(ERR_PERM_DENIED, file, P_OBJ | F_AST | F_ENV, 126);
	else
		exittool(ERR_NOT_EXECUTABLE, file, P_OBJ | F_AST | F_ENV, 126);
}

// print error and exit with cleanup flags
int	exittool(char *msg, void *obj, int action, unsigned char code)
{
	if (action & OPEN_FAIL)
		open_fail(obj);
	if (action & EXEC_FAIL)
		exec_fail(obj);
	if (msg && obj && (action & P_OBJ) && (action & STRERR))
		ft_fprintf(2, msg, obj, strerror(errno));
	else if (msg && (action & STRERR))
		ft_fprintf(2, msg, strerror(errno));
	else if (msg && obj && (action & P_OBJ))
		ft_fprintf(2, msg, obj);
	else if (msg)
		ft_fprintf(2, msg);
	if (action & F_AST && (!(action & PPROC) || (action & TRUE_EXIT)))
		free_ast_root();
	if (action & F_ENV && (!(action & PPROC) || (action & TRUE_EXIT)))
		initenv(NULL);
	if (action & F_ARR)
		free_array((char **)obj);
	if (obj && (action & F_OBJ))
		free(obj);
	if (msg && (action & F_MSG))
		free(msg);
	if ((action & STAY || action & PPROC) && !(action & TRUE_EXIT))
		return (code);
	exit(code);
}
