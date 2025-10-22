/* AST Execution Test Suite */
#include "execution.h"
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

// Helper to duplicate string array on heap
static char **dup_argv(char **argv)
{
	int i;
	char **new;

	i = 0;
	while (argv[i])
		i++;
	new = malloc((i + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	while (argv[++i])
	{
		new[i] = ft_strdup(argv[i]);
		if (!new[i])
			return (NULL);
	}
	new[i] = NULL;
	return (new);
}

// Create heap-allocated AST for single command
void run_cmd(char **argv)
{
	t_ast *ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return ;
	ast->type = CMD;
	ast->cmd.argv = dup_argv(argv);
	ast->cmd.redirs = NULL;
	if (!ast->cmd.argv)
	{
		free(ast);
		return ;
	}
	execute_ast(ast);
}

// Create heap-allocated AST for pipe
void run_pipe(char **left_argv, char **right_argv)
{
	t_ast *left;
	t_ast *right;
	t_ast *pipe;

	left = malloc(sizeof(t_ast));
	right = malloc(sizeof(t_ast));
	pipe = malloc(sizeof(t_ast));
	if (!left || !right || !pipe)
		return ;
	left->type = CMD;
	left->cmd.argv = dup_argv(left_argv);
	left->cmd.redirs = NULL;
	right->type = CMD;
	right->cmd.argv = dup_argv(right_argv);
	right->cmd.redirs = NULL;
	if (!left->cmd.argv || !right->cmd.argv)
		return ;
	pipe->type = PIPE;
	pipe->s_pipe.left = left;
	pipe->s_pipe.right = right;
	execute_ast(pipe);
}

void test_echo(void)
{
	char *args1[] = {"echo", "hello", "world", NULL};
	char *args2[] = {"echo", "-n", "no_newline", NULL};
	char *args3[] = {"echo", "-nnn", "multiple_n", NULL};
	char *args4[] = {"echo", NULL};
	
	printf("\n=== ECHO TESTS ===\n");
	printf("Test: echo hello world\n");
	run_cmd(args1);
	printf("\nTest: echo -n no_newline\n");
	run_cmd(args2);
	printf(" <--should be no newline\n");
	printf("\nTest: echo -nnn multiple_n\n");
	run_cmd(args3);
	printf(" <--should be no newline\n");
	printf("\nTest: echo (empty)\n");
	run_cmd(args4);
}

void test_pwd_env(void)
{
	char *pwd[] = {"pwd", NULL};
	char *env[] = {"env", NULL};
	char *head[] = {"head", "-3", NULL};
	
	printf("\n=== PWD/ENV TESTS ===\n");
	printf("Test: pwd\n");
	run_cmd(pwd);
	printf("\nTest: env (showing first 3 via head)\n");
	run_pipe(env, head);
}

void test_export_unset(void)
{
	char *exp1[] = {"export", "TEST_VAR=hello", NULL};
	char *exp2[] = {"export", "123invalid", NULL};
	char *uns1[] = {"unset", "TEST_VAR", NULL};
	char *uns2[] = {"unset", "123invalid", NULL};
	
	printf("\n=== EXPORT/UNSET TESTS ===\n");
	printf("Test: export TEST_VAR=hello\n");
	run_cmd(exp1);
	printf("\nTest: export 123invalid (should error)\n");
	run_cmd(exp2);
	printf("\nTest: unset TEST_VAR\n");
	run_cmd(uns1);
	printf("\nTest: unset 123invalid (silent)\n");
	run_cmd(uns2);
}

void test_cd(void)
{
	char *cd1[] = {"cd", "/tmp", NULL};
	char *pwd[] = {"pwd", NULL};
	char *cd2[] = {"cd", "-", NULL};
	char *cd3[] = {"cd", "..", NULL};
	char *cd4[] = {"cd", "a", "b", NULL};
	char *cd5[] = {"cd", "/nonexistent", NULL};
	
	printf("\n=== CD TESTS ===\n");
	printf("Test: cd /tmp && pwd\n");
	run_cmd(cd1);
	run_cmd(pwd);
	printf("\nTest: cd - && pwd\n");
	run_cmd(cd2);
	run_cmd(pwd);
	printf("\nTest: cd .. && pwd\n");
	run_cmd(cd3);
	run_cmd(pwd);
	printf("\nTest: cd a b (too many args)\n");
	run_cmd(cd4);
	printf("\nTest: cd /nonexistent (should error)\n");
	run_cmd(cd5);
}

void test_pipes(void)
{
	char *echo[] = {"echo", "hello_pipe", NULL};
	char *cat[] = {"cat", NULL};
	char *grep[] = {"grep", "pipe", NULL};
	char *ls[] = {"ls", "-l", NULL};
	char *head[] = {"head", "-5", NULL};
	
	printf("\n=== PIPE TESTS ===\n");
	printf("Test: echo hello_pipe | cat\n");
	run_pipe(echo, cat);
	printf("\nTest: echo hello_pipe | grep pipe\n");
	run_pipe(echo, grep);
	printf("\nTest: ls -l | head -5\n");
	run_pipe(ls, head);
}

void test_builtin_pipe(void)
{
	char *pwd[] = {"pwd", NULL};
	char *cat[] = {"cat", NULL};
	char *echo[] = {"echo", "builtin", NULL};
	char *grep[] = {"grep", "built", NULL};
	
	printf("\n=== BUILTIN IN PIPE ===\n");
	printf("Test: pwd | cat\n");
	run_pipe(pwd, cat);
	printf("\nTest: echo builtin | grep built\n");
	run_pipe(echo, grep);
}

void test_errors(void)
{
	char *invalid[] = {"nonexistent_cmd_xyz", NULL};
	char *no_file[] = {"/bin/nonexistent_file", NULL};
	
	printf("\n=== ERROR TESTS ===\n");
	printf("Test: nonexistent_cmd_xyz (command not found)\n");
	run_cmd(invalid);
	printf("\nTest: /bin/nonexistent_file (no such file)\n");
	run_cmd(no_file);
}

int main(void)
{
	printf("=== AST EXECUTION TEST SUITE ===\n");
	
	if (initenv(environ) == -1)
	{
		printf("ERROR: Failed to initialize environment\n");
		return (1);
	}
	
	test_echo();
	test_pwd_env();
	test_export_unset();
	test_cd();
	test_pipes();
	test_builtin_pipe();
	test_errors();
	
	printf("\n=== ALL TESTS COMPLETE ===\n");
	initenv(NULL);
	return (0);
}
