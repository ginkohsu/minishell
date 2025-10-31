/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:06:13 by jinxu             #+#    #+#             */
/*   Updated: 2025/10/26 21:37:49 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0; //initialize

void	sig_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	test_parser(char *input)
{
	t_ast	*ast;
	int		token_count;
	t_token	*tokens;

	printf("\n=== Testing: '%s' ===\n", input);
	
	// Test tokenization
	tokens = tokenize(input, &token_count);
	if (!tokens)
	{
		printf("Tokenization failed!\n");
		return ;
	}
	printf("--- Tokens ---\n");
	print_tokens_debug(tokens, token_count);
	
	// Test parsing
	ast = parse(input);
	if (!ast)
	{
		printf("Parsing failed!\n");
		free_tokens(tokens, token_count);
		return ;
	}
	
	printf("--- AST ---\n");
	print_ast(ast, 0);
	
	// Cleanup
	free_ast(ast);
	free_tokens(tokens, token_count);
	printf("=== End Test ===\n\n");
}

static void	run_automated_tests(void)
{
	printf("Running automated parser tests...\n\n");
	
	// Basic commands
	test_parser("ls -la");
	test_parser("echo hello world");
	
	// Redirections
	test_parser("cat < input.txt");
	test_parser("ls > output.txt");
	test_parser("cat >> append.txt");
	test_parser("cat << EOF");
	
	// Pipes
	test_parser("ls | grep test");
	test_parser("cat file.txt | grep pattern | wc -l");
	
	// Combined
	test_parser("ls -la | grep test > output.txt");
	test_parser("cat < input.txt | grep pattern >> log.txt");
	
	// Quotes and environment variables
	test_parser("echo \"hello $USER\"");
	test_parser("echo 'hello $USER'");
	test_parser("echo $HOME");
	test_parser("echo $?");
	
	// Edge cases
	test_parser("");
	test_parser("   ");
	test_parser("ls    -la   ");
}

static void	run_interactive_mode(void)
{
	char	*line;
	t_ast	*ast;

	printf("Entering interactive mode. Type commands to test parser.\n");
	printf("Type 'exit' to quit, 'test' to run automated tests.\n\n");
	
	while (1)
	{
		line = readline("parser_test$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
		if (ft_strcmp(line, "test") == 0)
		{
			free(line);
			run_automated_tests();
			continue ;
		}
		
		ast = parse(line);
		if (ast)
		{
			printf("--- Parser Output ---\n");
			print_ast(ast, 0);
			free_ast(ast);
		}
		else
		{
			printf("Parser: syntax error or empty command\n");
		}
		free(line);
	}
}

int	main(int argc, char **argv)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	
	if (argc == 2 && ft_strcmp(argv[1], "--test") == 0)
		run_automated_tests();
	else if (argc == 2)
		test_parser(argv[1]);
	else
		run_interactive_mode();
	
	return (0);
}
