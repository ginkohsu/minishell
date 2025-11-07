/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 03:54:23 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/22 03:54:25 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_ast	*g_ast_root = NULL;

static void		recursive_exec(t_ast *ast, t_pipe_ctx *ctx);
static void		cycle_pipes(t_pipe_ctx *ctx);

// main entry point for ast execution
void	execute_ast(t_ast *ast)
{
	t_pipe_ctx	ctx;
	char		*tmp;

	if (!ast || (ast->type == CMD && (!ast->cmd.argv || !ast->cmd.argv[0])))
		return ;
	if (ast->type == CMD && is_builtin(ast->cmd.argv[0]) && !ast->cmd.redirs)
	{
		tmp = ft_strprep("?=", ft_itoa(parent_builtin(&ast->cmd)));
		if (!tmp || addenv(tmp) == -1)
			exittool(ERR_ENV_CORRUPT, tmp, F_OBJ, 1);
		free(tmp);
		return ;
	}
	ast_root(ast);
	ctx.total = count_ast_commands(ast);
	ctx.pid = malloc(ctx.total * sizeof(int));
	if (!ctx.pid)
	{
		free_ast(ast);
		return ;
	}
	ctx.index = 0;
	recursive_exec(ast, &ctx);
	wait_for_children(ctx.pid, ctx.total);
	ast_root(NULL);
}

// set or free root of ast
void	ast_root(t_ast *ast)
{
	if (ast)
	{
		if (g_ast_root && g_ast_root != ast)
			free_ast(g_ast_root);
		g_ast_root = ast;
	}
	else
	{
		if (g_ast_root)
			free_ast(g_ast_root);
		g_ast_root = NULL;
	}
}

// recursively count total commands in ast
int	count_ast_commands(t_ast *ast)
{
	if (!ast)
		return (0);
	if (ast->type == CMD)
		return (1);
	return (count_ast_commands(ast->s_pipe.left)
		+ count_ast_commands(ast->s_pipe.right));
}

static void	recursive_exec(t_ast *ast, t_pipe_ctx *ctx)
{
	if (ast->type == CMD)
	{
		if (ctx->index < ctx->total - 1 && pipe(ctx->fd[NEXT]) == -1)
			exittool(ERR_PIPE, ctx->pid, F_OBJ | F_AST | STRERR, 1);
		ctx->pid[ctx->index] = fork();
		if (ctx->pid[ctx->index] == -1)
			exittool(ERR_FORK, ctx->pid, F_OBJ | F_AST | STRERR, 1);
		if (ctx->pid[ctx->index] == 0)
		{
			if (ctx->total == 1)
				only_child(&ast->cmd, ctx->fd);
			else if (ctx->index == 0)
				first_child(&ast->cmd, ctx->fd);
			else if (ctx->index == ctx->total - 1)
				last_child(&ast->cmd, ctx->fd);
			else
				middle_child(&ast->cmd, ctx->fd);
		}
		cycle_pipes(ctx);
	}
	else if (ast->type == PIPE)
	{
		recursive_exec(ast->s_pipe.left, ctx);
		recursive_exec(ast->s_pipe.right, ctx);
	}
}

static void	cycle_pipes(t_pipe_ctx *ctx)
{
	if (ctx->index > 0)
	{
		safe_close(&ctx->fd[LAST][WRITE]);
		safe_close(&ctx->fd[LAST][READ]);
	}
	if (ctx->index < ctx->total - 1)
	{
		ctx->fd[LAST][WRITE] = ctx->fd[NEXT][WRITE];
		ctx->fd[LAST][READ] = ctx->fd[NEXT][READ];
		ctx->index++;
	}
}
