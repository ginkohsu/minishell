/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:05:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/09 19:05:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
** Debug utility functions - currently static/unused.
** To enable: remove 'static' keyword and add prototype to execution.h
**
** These functions provide detailed tracing for:
** - Command execution flow
** - Pipe context state
** - File descriptor management
** - PATH resolution
** - Environment operations
** - AST structure visualization
*/

/*
** Debug flag - set to 1 to enable debug output
** Easy to toggle on/off during development
*/
static int	g_dbg_enabled = 0;

/*
** Print debug message to stderr with [DBG] prefix
*/
__attribute__((unused)) static void dbg_print(char *msg)
{
	if (!g_dbg_enabled)
		return ;
	ft_fprintf(2, "[DBG] %s", msg);
}

/*
** Print AST structure recursively for debugging
*/
__attribute__((unused)) static void dbg_print_ast(t_ast *ast, int depth)
{
	int	i;

	if (!g_dbg_enabled || !ast)
		return ;
	i = -1;
	while (++i < depth)
		ft_fprintf(2, "  ");
	if (ast->type == CMD)
	{
		ft_fprintf(2, "CMD: %s", ast->cmd.argv[0]);
		i = 0;
		while (ast->cmd.argv[++i])
			ft_fprintf(2, " %s", ast->cmd.argv[i]);
		if (ast->cmd.redirs)
			ft_fprintf(2, " [has redirections]");
		ft_fprintf(2, "\n");
	}
	else
	{
		ft_fprintf(2, "PIPE:\n");
		dbg_print_ast(ast->s_pipe.left, depth + 1);
		dbg_print_ast(ast->s_pipe.right, depth + 1);
	}
}

/*
** Print command execution trace
*/
__attribute__((unused)) static void dbg_trace_cmd(char *location,
	char *cmd_name)
{
	if (!g_dbg_enabled)
		return ;
	ft_fprintf(2, "[DBG] %s: executing '%s'\n", location, cmd_name);
}

/*
** Print pipe context state
*/
__attribute__((unused)) static void dbg_trace_pipe(char *location, int index,
	int total)
{
	if (!g_dbg_enabled)
		return ;
	ft_fprintf(2, "[DBG] %s: cmd %d/%d\n", location, index + 1, total);
}

/*
** Print file descriptor state
*/
__attribute__((unused)) static void dbg_trace_fds(char *location, int fd[3][2])
{
	if (!g_dbg_enabled)
		return ;
	ft_fprintf(2, "[DBG] %s: FDs - NEXT[%d,%d] LAST[%d,%d] IOFD[%d,%d]\n",
		location, fd[NEXT][READ], fd[NEXT][WRITE], fd[LAST][READ],
		fd[LAST][WRITE], fd[IOFD][READ], fd[IOFD][WRITE]);
}

/*
** Print child process role
*/
__attribute__((unused)) static void dbg_trace_child(char *role, char *cmd_name)
{
	if (!g_dbg_enabled)
		return ;
	ft_fprintf(2, "[DBG] Child (%s): %s\n", role, cmd_name);
}

/*
** Print PATH lookup attempt
*/
__attribute__((unused)) static void dbg_trace_path(char *prog, char *path)
{
	if (!g_dbg_enabled)
		return ;
	if (path)
		ft_fprintf(2, "[DBG] PATH: '%s' -> '%s'\n", prog, path);
	else
		ft_fprintf(2, "[DBG] PATH: '%s' -> NOT FOUND\n", prog);
}

/*
** Print environment operation
*/
__attribute__((unused)) static void dbg_trace_env(char *operation, char *key)
{
	if (!g_dbg_enabled)
		return ;
	ft_fprintf(2, "[DBG] ENV %s: %s\n", operation, key);
}

/*
** Toggle debug output on/off
*/
__attribute__((unused)) static void dbg_toggle(void)
{
	g_dbg_enabled = !g_dbg_enabled;
	if (g_dbg_enabled)
		ft_fprintf(2, "[DBG] Debug output ENABLED\n");
	else
		ft_fprintf(2, "[DBG] Debug output DISABLED\n");
}

/*
** Enable debug output
*/
__attribute__((unused)) static void dbg_enable(void)
{
	g_dbg_enabled = 1;
}

/*
** Disable debug output
*/
__attribute__((unused)) static void dbg_disable(void)
{
	g_dbg_enabled = 0;
}
