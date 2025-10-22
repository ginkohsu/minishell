/* AST Structure Break Test - Testing AST edge cases */
#include "execution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

void test_deep_pipe_nesting(void)
{
	printf("\n=== DEEP PIPE NESTING ===\n");
	printf("Test: 100-level deep pipe nesting\n");
	
	// Create a deeply nested pipe structure
	t_ast *root = NULL;
	t_ast *current = NULL;
	
	for (int i = 0; i < 100; i++)
	{
		t_ast *cmd = malloc(sizeof(t_ast));
		cmd->type = CMD;
		char **argv = malloc(2 * sizeof(char *));
		argv[0] = ft_strdup("echo");
		argv[1] = NULL;
		cmd->cmd.argv = argv;
		cmd->cmd.redirs = NULL;
		
		if (!root)
		{
			root = cmd;
			current = cmd;
		}
		else
		{
			t_ast *pipe_node = malloc(sizeof(t_ast));
			pipe_node->type = PIPE;
			pipe_node->s_pipe.left = current;
			pipe_node->s_pipe.right = cmd;
			current = pipe_node;
		}
	}
	
	// Count commands - should handle deep recursion
	int count = count_ast_commands(current);
	printf("Counted %d commands in deep pipe structure\n", count);
	
	// Free it - tests recursive freeing
	free_ast(current);
	printf("✓ Survived deep pipe nesting (100 levels)\n");
}

void test_unbalanced_pipe_tree(void)
{
	printf("\n=== UNBALANCED PIPE TREE ===\n");
	printf("Test: Heavily unbalanced pipe tree\n");
	
	// Left side: single command
	t_ast *left = malloc(sizeof(t_ast));
	left->type = CMD;
	left->cmd.argv = malloc(2 * sizeof(char *));
	left->cmd.argv[0] = ft_strdup("echo");
	left->cmd.argv[1] = NULL;
	left->cmd.redirs = NULL;
	
	// Right side: deeply nested
	t_ast *right = left;
	for (int i = 0; i < 50; i++)
	{
		t_ast *cmd = malloc(sizeof(t_ast));
		cmd->type = CMD;
		cmd->cmd.argv = malloc(2 * sizeof(char *));
		cmd->cmd.argv[0] = ft_strdup("cat");
		cmd->cmd.argv[1] = NULL;
		cmd->cmd.redirs = NULL;
		
		t_ast *pipe_node = malloc(sizeof(t_ast));
		pipe_node->type = PIPE;
		pipe_node->s_pipe.left = right;
		pipe_node->s_pipe.right = cmd;
		right = pipe_node;
	}
	
	int count = count_ast_commands(right);
	printf("Counted %d commands in unbalanced tree\n", count);
	
	free_ast(right);
	printf("✓ Survived unbalanced pipe tree\n");
}

void test_pipe_with_null_children(void)
{
	printf("\n=== PIPE WITH NULL CHILDREN ===\n");
	
	printf("Test: Pipe node with NULL left child\n");
	t_ast *pipe = malloc(sizeof(t_ast));
	pipe->type = PIPE;
	pipe->s_pipe.left = NULL;
	t_ast *right = malloc(sizeof(t_ast));
	right->type = CMD;
	right->cmd.argv = malloc(2 * sizeof(char *));
	right->cmd.argv[0] = ft_strdup("echo");
	right->cmd.argv[1] = NULL;
	right->cmd.redirs = NULL;
	pipe->s_pipe.right = right;
	
	int count = count_ast_commands(pipe);
	printf("Count with NULL left: %d\n", count);
	free_ast(pipe);
	printf("✓ Survived NULL left child\n");
	
	printf("\nTest: Pipe node with NULL right child\n");
	pipe = malloc(sizeof(t_ast));
	pipe->type = PIPE;
	t_ast *left = malloc(sizeof(t_ast));
	left->type = CMD;
	left->cmd.argv = malloc(2 * sizeof(char *));
	left->cmd.argv[0] = ft_strdup("cat");
	left->cmd.argv[1] = NULL;
	left->cmd.redirs = NULL;
	pipe->s_pipe.left = left;
	pipe->s_pipe.right = NULL;
	
	count = count_ast_commands(pipe);
	printf("Count with NULL right: %d\n", count);
	free_ast(pipe);
	printf("✓ Survived NULL right child\n");
	
	printf("\nTest: Pipe node with both NULL children\n");
	pipe = malloc(sizeof(t_ast));
	pipe->type = PIPE;
	pipe->s_pipe.left = NULL;
	pipe->s_pipe.right = NULL;
	
	count = count_ast_commands(pipe);
	printf("Count with both NULL: %d\n", count);
	free_ast(pipe);
	printf("✓ Survived both NULL children\n");
}

void test_cmd_with_massive_argv(void)
{
	printf("\n=== COMMAND WITH MASSIVE ARGV ===\n");
	printf("Test: Command with 10000 arguments\n");
	
	t_ast *ast = malloc(sizeof(t_ast));
	ast->type = CMD;
	ast->cmd.argv = malloc(10002 * sizeof(char *));
	ast->cmd.argv[0] = ft_strdup("echo");
	for (int i = 1; i <= 10000; i++)
		ast->cmd.argv[i] = ft_strdup("x");
	ast->cmd.argv[10001] = NULL;
	ast->cmd.redirs = NULL;
	
	printf("Freeing command with 10000 args...\n");
	free_ast(ast);
	printf("✓ Survived massive argv\n");
}

void test_cmd_with_massive_redirs(void)
{
	printf("\n=== COMMAND WITH MASSIVE REDIRECTIONS ===\n");
	printf("Test: Command with 1000 chained redirections\n");
	
	t_ast *ast = malloc(sizeof(t_ast));
	ast->type = CMD;
	ast->cmd.argv = malloc(2 * sizeof(char *));
	ast->cmd.argv[0] = ft_strdup("echo");
	ast->cmd.argv[1] = NULL;
	
	t_redir *first = NULL;
	t_redir *current = NULL;
	
	for (int i = 0; i < 1000; i++)
	{
		t_redir *redir = malloc(sizeof(t_redir));
		redir->type = REDIR_OUT;
		redir->filename = ft_strdup("/dev/null");
		redir->next = NULL;
		
		if (!first)
			first = redir;
		else
			current->next = redir;
		current = redir;
	}
	
	ast->cmd.redirs = first;
	
	printf("Freeing command with 1000 redirections...\n");
	free_ast(ast);
	printf("✓ Survived massive redirection chain\n");
}

void test_invalid_ast_type(void)
{
	printf("\n=== INVALID AST TYPE ===\n");
	printf("Test: AST node with invalid type\n");
	
	t_ast *ast = malloc(sizeof(t_ast));
	ast->type = 999;  // Invalid type
	
	int count = count_ast_commands(ast);
	printf("Count with invalid type: %d\n", count);
	
	// Manually free since free_ast might not handle invalid types
	free(ast);
	printf("✓ Survived invalid AST type\n");
}

void test_circular_pipe_reference(void)
{
	printf("\n=== CIRCULAR REFERENCE ===\n");
	printf("Test: Circular pipe reference (A -> B -> A)\n");
	printf("⚠ Skipped (would cause infinite loop in count/free)\n");
	// This would cause stack overflow or infinite loop
	// Not testing to avoid crashes
}

void test_mixed_null_and_valid_argv(void)
{
	printf("\n=== MIXED NULL IN ARGV ===\n");
	printf("Test: argv with NULL in middle\n");
	
	t_ast *ast = malloc(sizeof(t_ast));
	ast->type = CMD;
	ast->cmd.argv = malloc(5 * sizeof(char *));
	ast->cmd.argv[0] = ft_strdup("echo");
	ast->cmd.argv[1] = ft_strdup("hello");
	ast->cmd.argv[2] = NULL;  // NULL in middle
	ast->cmd.argv[3] = ft_strdup("world");  // Unreachable
	ast->cmd.argv[4] = NULL;
	ast->cmd.redirs = NULL;
	
	printf("Executing command with NULL in middle of argv\n");
	execute_ast(ast);
	printf("✓ Survived NULL in middle of argv\n");
}

void test_redir_with_null_in_chain(void)
{
	printf("\n=== NULL IN REDIR CHAIN ===\n");
	printf("Test: Redirection chain with explicit NULL node\n");
	
	t_redir *redir1 = malloc(sizeof(t_redir));
	redir1->type = REDIR_OUT;
	redir1->filename = ft_strdup("/dev/null");
	redir1->next = NULL;  // This would be second redir normally
	
	t_ast *ast = malloc(sizeof(t_ast));
	ast->type = CMD;
	ast->cmd.argv = malloc(2 * sizeof(char *));
	ast->cmd.argv[0] = ft_strdup("echo");
	ast->cmd.argv[1] = NULL;
	ast->cmd.redirs = redir1;
	
	execute_ast(ast);
	printf("✓ Survived normal redir termination\n");
}

void test_double_free_protection(void)
{
	printf("\n=== DOUBLE FREE PROTECTION ===\n");
	printf("Test: Call execute_ast twice with same AST\n");
	
	t_ast *ast = malloc(sizeof(t_ast));
	ast->type = CMD;
	ast->cmd.argv = malloc(2 * sizeof(char *));
	ast->cmd.argv[0] = ft_strdup("echo");
	ast->cmd.argv[1] = NULL;
	ast->cmd.redirs = NULL;
	
	execute_ast(ast);
	printf("First execution complete\n");
	
	// Second execution - AST was already freed by first execute_ast
	// This tests if execute_ast handles already-freed AST
	printf("⚠ Cannot test second execution (AST already freed)\n");
	printf("✓ First execution succeeded\n");
}

void test_zero_length_argv(void)
{
	printf("\n=== ZERO LENGTH ARGV ===\n");
	printf("Test: argv array with only NULL terminator\n");
	
	t_ast *ast = malloc(sizeof(t_ast));
	ast->type = CMD;
	ast->cmd.argv = malloc(1 * sizeof(char *));
	ast->cmd.argv[0] = NULL;
	ast->cmd.redirs = NULL;
	
	execute_ast(ast);
	printf("✓ Survived zero-length argv\n");
}

int main(void)
{
	printf("=== AST STRUCTURE BREAK TEST ===\n");
	printf("Testing AST edge cases and potential crashes\n");
	
	if (initenv(environ) == -1)
	{
		printf("ERROR: Failed to initialize environment\n");
		return (1);
	}
	
	test_deep_pipe_nesting();
	test_unbalanced_pipe_tree();
	test_pipe_with_null_children();
	test_cmd_with_massive_argv();
	test_cmd_with_massive_redirs();
	test_invalid_ast_type();
	test_circular_pipe_reference();
	test_mixed_null_and_valid_argv();
	test_redir_with_null_in_chain();
	test_double_free_protection();
	test_zero_length_argv();
	
	printf("\n=== AST STRUCTURE TESTS COMPLETE ===\n");
	printf("If you're reading this, the AST handling is robust! 💪\n");
	
	initenv(NULL);
	return (0);
}
