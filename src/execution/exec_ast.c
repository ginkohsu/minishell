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

static void		recursive_exec(t_ast *ast, t_pipe_ctx *ctx, int total);
static void		cycle_pipes(t_pipe_ctx *ctx, int total);

// main entry point for ast execution
void	execute_ast(t_ast *ast)
{
	t_pipe_ctx	ctx;
	int			total;
	char		*tmp;

	if (!ast || (ast->type == CMD && (!ast->cmd.argv || !ast->cmd.argv[0])))
		return ;
	if (ast->type == CMD && is_builtin(ast->cmd.argv[0]) && !ast->cmd.redirs)
	{
		tmp = ft_strprep("?=", ft_itoa(parent_builtin(&ast->cmd)));
		if (addenv(tmp) == -1)
			exittool(ERR_ENV_CORRUPT, tmp, F_OBJ, 1);
		free(tmp);
		return ;
	}
	free_ast_root();
	g_ast_root = ast;
	total = count_ast_commands(ast);
	ctx.pid = malloc(total * sizeof(int));
	if (!ctx.pid)
	{
		free_ast(ast);
		return ;
	}
	ctx.index = 0;
	recursive_exec(ast, &ctx, total);
	wait_for_children(ctx.pid, total);
	g_ast_root = NULL;
}

// free globally stored ast
void	free_ast_root(void)
{
	if (g_ast_root)
		free_ast(g_ast_root);
	g_ast_root = NULL;
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

static void	recursive_exec(t_ast *ast, t_pipe_ctx *ctx, int total)
{
	if (ast->type == CMD)
	{
		if (ctx->index < total - 1 && pipe(ctx->fd[NEXT]) == -1)
			exittool(ERR_PIPE, ctx->pid, F_OBJ | F_AST | STRERR, 1);
		ctx->pid[ctx->index] = fork();
		if (ctx->pid[ctx->index] == -1)
			exittool(ERR_FORK, ctx->pid, F_OBJ | F_AST | STRERR, 1);
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
		safe_close(&ctx->fd[LAST][WRITE]);
		safe_close(&ctx->fd[LAST][READ]);
	}
	if (ctx->index < total - 1)
	{
		ctx->fd[LAST][WRITE] = ctx->fd[NEXT][WRITE];
		ctx->fd[LAST][READ] = ctx->fd[NEXT][READ];
		ctx->index++;
	}
}
