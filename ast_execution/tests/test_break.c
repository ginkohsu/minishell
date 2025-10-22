/* Break Test Suite - Try to crash/leak execution engine */
#include "execution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

extern char **environ;

static char **dup_argv(char **argv)
{
	int i = 0;
	char **new;

	while (argv[i])
		i++;
	new = malloc((i + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	while (argv[++i])
		new[i] = ft_strdup(argv[i]);
	new[i] = NULL;
	return (new);
}

void run_cmd(char **argv)
{
	t_ast *ast = malloc(sizeof(t_ast));
	if (!ast)
		return ;
	ast->type = CMD;
	ast->cmd.argv = dup_argv(argv);
	ast->cmd.redirs = NULL;
	execute_ast(ast);
}

void test_null_checks(void)
{
	printf("\n=== NULL/EMPTY CHECKS ===\n");
	
	// Test empty command (should be safe - checked in execute_ast)
	printf("Test: NULL ast\n");
	execute_ast(NULL);
	printf("✓ Survived NULL AST\n");
	
	// Test with empty argv (parser should prevent but test anyway)
	printf("\nTest: Command with empty string\n");
	char *empty[] = {"", NULL};
	run_cmd(empty);
	printf("✓ Survived empty command\n");
}

void test_malformed_path(void)
{
	printf("\n=== MALFORMED PATH TESTS ===\n");
	
	printf("Test: PATH with empty components (::)\n");
	addenv("PATH=/bin::/usr/bin");
	char *ls1[] = {"ls", NULL};
	run_cmd(ls1);
	
	printf("\nTest: PATH=: (single colon)\n");
	addenv("PATH=:");
	char *ls2[] = {"/bin/ls", NULL};
	run_cmd(ls2);
	
	printf("\nTest: PATH=P (only 'P', less than 5 chars)\n");
	addenv("PATH=P");
	char *ls3[] = {"/bin/ls", NULL};
	run_cmd(ls3);
	
	printf("\nTest: Restore PATH\n");
	addenv("PATH=/usr/local/bin:/usr/bin:/bin");
}

void test_long_strings(void)
{
	char long_name[PATH_MAX + 100];
	char *cmd[2];
	int i;
	
	printf("\n=== LONG STRING TESTS ===\n");
	
	printf("Test: Command name longer than PATH_MAX\n");
	for (i = 0; i < PATH_MAX + 50; i++)
		long_name[i] = 'a';
	long_name[PATH_MAX + 50] = '\0';
	
	cmd[0] = long_name;
	cmd[1] = NULL;
	run_cmd(cmd);
	printf("✓ Survived very long command name\n");
}

void test_special_files(void)
{
	printf("\n=== SPECIAL FILE TESTS ===\n");
	
	printf("Test: Execute /dev/null\n");
	char *null[] = {"/dev/null", NULL};
	run_cmd(null);
	
	printf("\nTest: Execute /dev/zero\n");
	char *zero[] = {"/dev/zero", NULL};
	run_cmd(zero);
	
	printf("\nTest: Execute /proc/self/exe (recursive!)\n");
	// Skip this test - it causes infinite recursion
	printf("⚠ Skipped to avoid infinite recursion\n");
}

void test_symlinks(void)
{
	printf("\n=== SYMLINK TESTS ===\n");
	
	// Create a symlink loop
	system("ln -sf link1 /tmp/minishell_link2 2>/dev/null");
	system("ln -sf link2 /tmp/minishell_link1 2>/dev/null");
	
	printf("Test: Execute circular symlink\n");
	char *link[] = {"/tmp/minishell_link1", NULL};
	run_cmd(link);
	
	system("rm -f /tmp/minishell_link1 /tmp/minishell_link2");
	printf("✓ Survived circular symlink\n");
}

void test_many_args(void)
{
	char **args;
	int i;
	
	printf("\n=== MANY ARGUMENTS TEST ===\n");
	printf("Test: Command with 1000 arguments\n");
	
	args = malloc(1002 * sizeof(char *));
	args[0] = ft_strdup("echo");
	for (i = 1; i <= 1000; i++)
		args[i] = ft_strdup("arg");
	args[1001] = NULL;
	
	run_cmd(args);
	
	printf("✓ Survived 1000 arguments\n");
}

void test_env_corruption(void)
{
	int i;
	char var[100];
	
	printf("\n=== ENVIRONMENT CORRUPTION TEST ===\n");
	printf("Test: Add 100 environment variables\n");
	
	for (i = 0; i < 100; i++)
	{
		sprintf(var, "TEST_VAR_%d=value_%d", i, i);
		if (addenv(var) == -1)
		{
			printf("✗ Failed to add variable %d\n", i);
			break ;
		}
	}
	
	printf("✓ Added 100 environment variables\n");
	
	printf("Test: Remove all test variables\n");
	for (i = 0; i < 100; i++)
	{
		sprintf(var, "TEST_VAR_%d", i);
		rmenv(var);
	}
	printf("✓ Removed all test variables\n");
}

void test_fd_limits(void)
{
	printf("\n=== FILE DESCRIPTOR LIMITS ===\n");
	printf("Test: Open many files (testing ulimit)\n");
	
	int fds[100];
	int i;
	int max_fd = 0;
	
	for (i = 0; i < 100; i++)
	{
		fds[i] = open("/dev/null", O_RDONLY);
		if (fds[i] == -1)
			break ;
		max_fd = i;
	}
	
	printf("Opened %d file descriptors\n", max_fd + 1);
	
	printf("Test: Run command with many FDs open\n");
	char *ls[] = {"/bin/ls", NULL};
	run_cmd(ls);
	
	// Close all
	for (i = 0; i <= max_fd; i++)
		close(fds[i]);
	
	printf("✓ Survived FD stress test\n");
}

void test_pipe_stress(void)
{
	printf("\n=== PIPE STRESS TEST ===\n");
	printf("Test: Would need parser for multi-pipe - skipping\n");
	printf("(This would test 50+ pipe chain)\n");
}

int main(void)
{
	printf("=== BREAK TEST SUITE ===\n");
	printf("Attempting to crash/leak the execution engine\n");
	
	if (initenv(environ) == -1)
	{
		printf("ERROR: Failed to initialize environment\n");
		return (1);
	}
	
	test_null_checks();
	test_malformed_path();
	test_long_strings();
	test_special_files();
	test_symlinks();
	test_many_args();
	test_env_corruption();
	test_fd_limits();
	test_pipe_stress();
	
	printf("\n=== BREAK TESTS COMPLETE ===\n");
	printf("If you're reading this, the engine survived! 🎉\n");
	
	initenv(NULL);
	return (0);
}
