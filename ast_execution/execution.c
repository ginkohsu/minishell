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

static int	recursive_count(t_ast *ast);
static void	recursive_exec(t_ast *ast, t_pipe_ctx *ctx, int total);
static void	cycle_pipes(t_pipe_ctx *ctx, int total);

void	execute_ast(t_ast *ast)
{
	t_pipe_ctx	ctx;
	int			total;
	int			i;

	if (!ast || (ast->type == CMD && (!ast->cmd.argv || !ast->cmd.argv[0])))
		return ;
	free_ast_root();
	if (ast->type == CMD && is_builtin(ast->cmd.argv[0]) && !ast->cmd.redirs)
	{
		execute_parent_builtin(&ast->cmd);
		return ;
	}
	g_ast_root = ast;
	total = recursive_count(ast);
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
	i = -1;
	while (++i < total)
		waitpid(ctx.pid[i], NULL, 0);
	free(ctx.pid);
}

void	free_ast_root(void)
{
	free_ast(g_ast_root);
}

static int	recursive_count(t_ast *ast)
{
	if (!ast)
		return (0);
	if (ast->type == CMD)
		return (1);
	return (recursive_count(ast->pipe.left) + recursive_count(ast->pipe.right));
}

static void	recursive_exec(t_ast *ast, t_pipe_ctx *ctx, int total)
{
	if (ast->type == CMD)
	{
		if (ctx->index < total - 1 && pipe(ctx->fd[NEXT]) == -1)
			ft_error("pipe failed\nexecution.c:67\n", ctx->pid, F_OBJ | F_AST, 1);
		ctx->pid[ctx->index] = fork();
		if (ctx->pid[ctx->index] == -1)
			ft_error("fork failed\nexecution.c:70\n", ctx->pid, F_OBJ | F_AST, 1);
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
		else if (ctx->index < total - 1)
			cycle_pipes(ctx, total);
	}
	else if (ast->type == PIPE)
	{
		recursive_exec(ast->pipe.left, ctx, total);
		recursive_exec(ast->pipe.right, ctx, total);
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
	ctx->index++;
}
