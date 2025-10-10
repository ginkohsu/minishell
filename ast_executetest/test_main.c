/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 01:22:30 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/10 01:22:31 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	main(void)
{
	t_ast	*ast;

	printf("=== Minishell Executor Complete Test ===\n");
	printf("Test case: echo " hello " | cat > output.txt\n");
	printf("This tests:\n");
	printf("1. Builtin command execution (echo)\n");
	printf("2. External command execution (cat, requires PATH lookup)\n");
	printf("3. Pipe functionality (|)\n");
	printf("4. Redirection functionality (> output.txt)\n");
	printf("5. Mixed execution of builtin and external commands\n\n");
	ast = create_test_ast();
	execute_ast(ast);
	free_ast(ast);
	printf("\n=== Test Complete ===\n");
	printf("Please check:\n");
	printf("1. output.txt file content should be \"hello\\n\"\n");
	printf("2. Pipe correctly transfers data\n");
	printf("3. External command cat is found via PATH and executed\n");
	return (0);
}
