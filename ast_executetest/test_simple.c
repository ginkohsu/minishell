/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:52:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/09 18:52:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"

/*
** Simple test: echo hello world | cat
** No redirections, just pipes and commands
*/
static t_ast	*create_simple_pipe_test(void)
{
	t_ast	*pipe_ast;
	t_ast	*left;
	t_ast	*right;

	right = malloc(sizeof(t_ast));
	right->type = CMD;
	right->cmd.argv = malloc(2 * sizeof(char *));
	right->cmd.argv[0] = ft_strdup("cat");
	right->cmd.argv[1] = NULL;
	right->cmd.redirs = NULL;
	left = malloc(sizeof(t_ast));
	left->type = CMD;
	left->cmd.argv = malloc(4 * sizeof(char *));
	left->cmd.argv[0] = ft_strdup("echo");
	left->cmd.argv[1] = ft_strdup("hello");
	left->cmd.argv[2] = ft_strdup("world");
	left->cmd.argv[3] = NULL;
	left->cmd.redirs = NULL;
	pipe_ast = malloc(sizeof(t_ast));
	pipe_ast->type = PIPE;
	pipe_ast->pipe.left = left;
	pipe_ast->pipe.right = right;
	return (pipe_ast);
}

/*
** Test single builtin command
*/
static t_ast	*create_single_builtin_test(void)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	ast->type = CMD;
	ast->cmd.argv = malloc(3 * sizeof(char *));
	ast->cmd.argv[0] = ft_strdup("echo");
	ast->cmd.argv[1] = ft_strdup("testing builtin");
	ast->cmd.argv[2] = NULL;
	ast->cmd.redirs = NULL;
	return (ast);
}

/*
** Test single external command
*/
static t_ast	*create_single_external_test(void)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	ast->type = CMD;
	ast->cmd.argv = malloc(3 * sizeof(char *));
	ast->cmd.argv[0] = ft_strdup("ls");
	ast->cmd.argv[1] = ft_strdup("-la");
	ast->cmd.argv[2] = NULL;
	ast->cmd.redirs = NULL;
	return (ast);
}

int	main(int argc, char **argv, char **envp)
{
	t_ast	*ast;
	int		test;

	(void)argv;
	initenv(envp);
	test = 1;
	if (argc > 1)
		test = ft_atoi(argv[1]);
	printf("=== Simple AST Execution Tests (No Redirections) ===\n\n");
	if (test == 1)
	{
		printf("Test 1: Single builtin command (echo)\n");
		printf("Expected output: testing builtin\n");
		printf("---\n");
		ast = create_single_builtin_test();
		execute_ast(ast);
		free_ast(ast);
	}
	else if (test == 2)
	{
		printf("Test 2: Single external command (ls -la)\n");
		printf("Expected: directory listing\n");
		printf("---\n");
		ast = create_single_external_test();
		execute_ast(ast);
		free_ast(ast);
	}
	else if (test == 3)
	{
		printf("Test 3: Pipe - echo hello world | cat\n");
		printf("Expected output: hello world\n");
		printf("---\n");
		ast = create_simple_pipe_test();
		execute_ast(ast);
		free_ast(ast);
	}
	else
	{
		printf("Unknown test number. Available tests:\n");
		printf("  1 - Single builtin\n");
		printf("  2 - Single external\n");
		printf("  3 - Pipe test\n");
		return (1);
	}
	printf("\n---\n=== Test Complete ===\n");
	return (0);
}
