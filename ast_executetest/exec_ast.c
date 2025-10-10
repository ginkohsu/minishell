/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:15:27 by aloimusa          #+#    #+#             */
/*   Updated: 2025/09/30 14:15:30 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_ast	*g_ast_root = NULL;

static void		recursive_exec(t_ast *ast, t_pipe_ctx *ctx, int total);
static void		cycle_pipes(t_pipe_ctx *ctx, int total);
static void		wait_for_children(int *pid, int total);

void	execute_ast(t_ast *ast)
{
	t_pipe_ctx	ctx;
	int			total;

	if (!ast || (ast->type == CMD && (!ast->cmd.argv || !ast->cmd.argv[0])))
		return ;
	if (ast->type == CMD && is_builtin(ast->cmd.argv[0]) && !ast->cmd.redirs)
	{
		addenv(ft_strprep("?=", ft_itoa(execute_parent_builtin(&ast->cmd))));
		return ;
	}
	free_ast_root();
	g_ast_root = ast;
	total = count_ast_commands(ast);
	ctx.pid = malloc(total * sizeof(int));
	if (!ctx.pid)
		return ;
	ctx.index = 0;
	recursive_exec(ast, &ctx, total);
	if (total > 1)
	{
		close(ctx.fd[LAST][WRITE]);
		close(ctx.fd[LAST][READ]);
	}
	wait_for_children(ctx.pid, total);
}

void	free_ast_root(void)
{
	free_ast(g_ast_root);
}

static void	wait_for_children(int *pid, int total)
{
	int		i;
	int		status;
	int		last_status;

	i = -1;
	while (++i < total - 1)
		waitpid(pid[i], &status, 0);
	last_status = 0;
	waitpid(pid[total - 1], &last_status, 0);
	free(pid);
	if (WIFEXITED(last_status))
		status = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
		status = 128 + WTERMSIG(last_status);
	else
		status = 1;
	addenv(ft_strprep("?=", ft_itoa(status)));
}

static void	recursive_exec(t_ast *ast, t_pipe_ctx *ctx, int total)
{
	if (ast->type == CMD)
	{
		if (ctx->index < total - 1 && pipe(ctx->fd[NEXT]) == -1)
			ft_error("pipe", ctx->pid, F_OBJ | F_AST | STRERROR, 1);
		ctx->pid[ctx->index] = fork();
		if (ctx->pid[ctx->index] == -1)
			ft_error("fork", ctx->pid, F_OBJ | F_AST | STRERROR, 1);
		if (ctx->pid[ctx->index] == 0)
		{
			if (total == 1)
				only_child(&ast->cmd, ctx->fd);
			else if (ctx->index == 0)
				first_child(&ast->cmd, ctx->fd);
			else if (ctx->index == total - 1)
				last_child(&ast->cmd, ctx->fd);
			else
				middle_child(&ast->cmd, ctx->fd);
		}
		cycle_pipes(ctx, total);
	}
	else if (ast->type == PIPE)
	{
		recursive_exec(ast->s_pipe.left, ctx, total);
		recursive_exec(ast->s_pipe.right, ctx, total);
	}
}

static void	cycle_pipes(t_pipe_ctx *ctx, int total)
{
	if (ctx->index > 0)
	{
		close(ctx->fd[LAST][WRITE]);
		close(ctx->fd[LAST][READ]);
	}
	if (ctx->index < total - 1)
	{
		ctx->fd[LAST][WRITE] = ctx->fd[NEXT][WRITE];
		ctx->fd[LAST][READ] = ctx->fd[NEXT][READ];
	}
	else
		return ;
	ctx->index++;
}
