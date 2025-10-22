/* Extended Break Test Suite - Redirection & Heredoc vulnerabilities */
#include "execution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

extern char **environ;

static t_ast *make_cmd_with_redir(char **argv, t_redir *redirs)
{
	t_ast *ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->type = CMD;
	ast->cmd.argv = argv;
	ast->cmd.redirs = redirs;
	return (ast);
}

static t_redir *make_redir(int type, char *filename)
{
	t_redir *redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = filename;
	redir->next = NULL;
	return (redir);
}

void test_null_filename_redir(void)
{
	printf("\n=== NULL FILENAME REDIRECTIONS ===\n");
	
	printf("Test: Output redirection with NULL filename\n");
	t_redir *redir = make_redir(REDIR_OUT, NULL);
	char *argv[] = {"echo", "test", NULL};
	t_ast *ast = make_cmd_with_redir(argv, redir);
	execute_ast(ast);
	printf("✓ Survived NULL filename in output redirect\n");
	
	printf("\nTest: Input redirection with NULL filename\n");
	redir = make_redir(REDIR_IN, NULL);
	ast = make_cmd_with_redir(argv, redir);
	execute_ast(ast);
	printf("✓ Survived NULL filename in input redirect\n");
}

void test_empty_filename_redir(void)
{
	printf("\n=== EMPTY FILENAME REDIRECTIONS ===\n");
	
	printf("Test: Output redirection with empty filename\n");
	t_redir *redir = make_redir(REDIR_OUT, "");
	char *argv[] = {"echo", "test", NULL};
	t_ast *ast = make_cmd_with_redir(argv, redir);
	execute_ast(ast);
	printf("✓ Survived empty filename in output redirect\n");
}

void test_special_filenames(void)
{
	printf("\n=== SPECIAL FILENAME REDIRECTIONS ===\n");
	
	printf("Test: Redirect to directory\n");
	t_redir *redir = make_redir(REDIR_OUT, "/tmp");
	char *argv[] = {"echo", "test", NULL};
	t_ast *ast = make_cmd_with_redir(argv, redir);
	execute_ast(ast);
	printf("✓ Survived redirect to directory\n");
	
	printf("\nTest: Redirect to read-only file\n");
	system("touch /tmp/minishell_readonly && chmod 000 /tmp/minishell_readonly");
	redir = make_redir(REDIR_OUT, "/tmp/minishell_readonly");
	ast = make_cmd_with_redir(argv, redir);
	execute_ast(ast);
	system("rm -f /tmp/minishell_readonly");
	printf("✓ Survived redirect to read-only file\n");
	
	printf("\nTest: Redirect from non-existent file\n");
	redir = make_redir(REDIR_IN, "/tmp/minishell_nonexistent_xyz123");
	ast = make_cmd_with_redir(argv, redir);
	execute_ast(ast);
	printf("✓ Survived redirect from non-existent file\n");
}

void test_long_filename_redir(void)
{
	char long_name[PATH_MAX + 100];
	int i;
	
	printf("\n=== LONG FILENAME REDIRECTIONS ===\n");
	printf("Test: Redirect to filename longer than PATH_MAX\n");
	
	strcpy(long_name, "/tmp/");
	for (i = 5; i < PATH_MAX + 50; i++)
		long_name[i] = 'a';
	long_name[PATH_MAX + 50] = '\0';
	
	t_redir *redir = make_redir(REDIR_OUT, long_name);
	char *argv[] = {"echo", "test", NULL};
	t_ast *ast = make_cmd_with_redir(argv, redir);
	execute_ast(ast);
	printf("✓ Survived very long filename redirect\n");
}

void test_many_redirections(void)
{
	printf("\n=== MANY REDIRECTIONS ===\n");
	printf("Test: 100 output redirections in chain\n");
	
	t_redir *first = NULL;
	t_redir *current = NULL;
	int i;
	char filename[50];
	
	for (i = 0; i < 100; i++)
	{
		sprintf(filename, "/tmp/minishell_redir_%d", i);
		t_redir *redir = make_redir(REDIR_OUT, ft_strdup(filename));
		if (!first)
			first = redir;
		else
			current->next = redir;
		current = redir;
	}
	
	char *argv[] = {"echo", "test", NULL};
	t_ast *ast = make_cmd_with_redir(argv, first);
	execute_ast(ast);
	
	system("rm -f /tmp/minishell_redir_*");
	printf("✓ Survived 100 redirections\n");
}

void test_heredoc_edge_cases(void)
{
	printf("\n=== HEREDOC EDGE CASES ===\n");
	
	printf("Test: Heredoc with NULL delimiter\n");
	(void)make_redir(REDIR_HEREDOC, NULL);
	printf("⚠ Skipped (would hang waiting for NULL delimiter)\n");
	
	printf("\nTest: Heredoc with empty delimiter\n");
	(void)make_redir(REDIR_HEREDOC, "");
	printf("⚠ Skipped (would match every line immediately)\n");
	
	printf("\nTest: Heredoc with very long delimiter\n");
	char long_delim[1000];
	memset(long_delim, 'X', 999);
	long_delim[999] = '\0';
	(void)make_redir(REDIR_HEREDOC, long_delim);
	printf("⚠ Skipped (requires interactive input)\n");
}

void test_redir_permission_issues(void)
{
	printf("\n=== REDIRECTION PERMISSION ISSUES ===\n");
	
	printf("Test: Output to /dev/full (no space device)\n");
	t_redir *redir = make_redir(REDIR_OUT, "/dev/full");
	char *argv[] = {"echo", "This should fail to write", NULL};
	t_ast *ast = make_cmd_with_redir(argv, redir);
	execute_ast(ast);
	printf("✓ Survived redirect to /dev/full\n");
	
	printf("\nTest: Output to /proc/self/mem (dangerous)\n");
	redir = make_redir(REDIR_OUT, "/proc/self/mem");
	ast = make_cmd_with_redir(argv, redir);
	execute_ast(ast);
	printf("✓ Survived redirect to /proc/self/mem\n");
}

void test_redir_race_conditions(void)
{
	printf("\n=== REDIRECTION RACE CONDITIONS ===\n");
	
	printf("Test: Redirect to symlink that gets deleted\n");
	system("ln -sf /tmp/minishell_target /tmp/minishell_symlink");
	system("rm -f /tmp/minishell_target");
	
	t_redir *redir = make_redir(REDIR_OUT, "/tmp/minishell_symlink");
	char *argv[] = {"echo", "test", NULL};
	t_ast *ast = make_cmd_with_redir(argv, redir);
	execute_ast(ast);
	
	system("rm -f /tmp/minishell_symlink /tmp/minishell_target");
	printf("✓ Survived redirect to broken symlink\n");
}

void test_multiple_heredocs(void)
{
	printf("\n=== MULTIPLE HEREDOCS ===\n");
	printf("Test: Command with multiple heredoc redirections\n");
	printf("⚠ Skipped (requires interactive input)\n");
}

void test_cmd_with_null_argv(void)
{
	printf("\n=== NULL ARGV TESTS ===\n");
	
	printf("Test: Command with NULL argv\n");
	t_ast *ast = malloc(sizeof(t_ast));
	ast->type = CMD;
	ast->cmd.argv = NULL;
	ast->cmd.redirs = NULL;
	execute_ast(ast);
	printf("✓ Survived NULL argv\n");
	
	printf("\nTest: Command with argv[0] = NULL\n");
	char *argv[] = {NULL};
	ast->cmd.argv = argv;
	execute_ast(ast);
	printf("✓ Survived argv[0] = NULL\n");
}

void test_fd_exhaustion_with_redirs(void)
{
	printf("\n=== FD EXHAUSTION WITH REDIRECTS ===\n");
	printf("Test: Many redirections without closing FDs properly\n");
	
	// Open many files first
	int fds[100];
	int i;
	for (i = 0; i < 100; i++)
	{
		fds[i] = open("/dev/null", O_RDONLY);
		if (fds[i] == -1)
			break;
	}
	
	printf("Opened %d FDs before test\n", i);
	
	t_redir *redir = make_redir(REDIR_OUT, "/tmp/minishell_fd_test");
	char *argv[] = {"echo", "test", NULL};
	t_ast *ast = make_cmd_with_redir(argv, redir);
	execute_ast(ast);
	
	// Close all FDs
	for (int j = 0; j < i; j++)
		close(fds[j]);
	
	system("rm -f /tmp/minishell_fd_test");
	printf("✓ Survived redirect with FD exhaustion\n");
}

int main(void)
{
	printf("=== EXTENDED BREAK TEST SUITE ===\n");
	printf("Testing redirection and heredoc vulnerabilities\n");
	
	if (initenv(environ) == -1)
	{
		printf("ERROR: Failed to initialize environment\n");
		return (1);
	}
	
	test_cmd_with_null_argv();
	test_null_filename_redir();
	test_empty_filename_redir();
	test_special_filenames();
	test_long_filename_redir();
	test_many_redirections();
	test_heredoc_edge_cases();
	test_redir_permission_issues();
	test_redir_race_conditions();
	test_multiple_heredocs();
	test_fd_exhaustion_with_redirs();
	
	printf("\n=== EXTENDED TESTS COMPLETE ===\n");
	printf("If you're reading this, the engine survived! 🔥\n");
	
	initenv(NULL);
	return (0);
}
