/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/10 12:58:25 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	main(void)
{
	test_init_list("echo '\"'hola'\"'chau", NULL);
	return (0);
} */

/* int	main(void)
{
	char	*input;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			return (0);
		test_init_list(input, NULL);
		free(input);
	}
	return (0);
} */

int	main(void)
{
	// Make sure the environment variables exist for testing
	setenv("USER", "john", 1);
	setenv("HOME", "/home/john", 1);
	setenv("VAR1", "42", 1);

	printf("\n%s===== $ EDGE CASES =====%s\n", CYAN, RESET);

	/* Single $ and empty cases */
	test_init_list("echo $user", "literal $");
	test_init_list("echo $$", "empty var name twice");
	test_init_list("echo $$$", "multiple empty vars");
	test_init_list("echo $ ", "$ followed by space");
	test_init_list("echo $\"", "$ before double quote");
	test_init_list("echo $'", "$ before single quote");

	printf("\n%s===== VARIABLE NAME BOUNDARIES =====%s\n", CYAN, RESET);

	/* Variable name termination */
	test_init_list("echo $USER.", "stop before dot");
	test_init_list("echo $USER!", "stop before exclamation");
	test_init_list("echo $USER$", "USER then empty");
	test_init_list("echo $USER123", "letters + digits");
	test_init_list("echo $_USER", "underscore start");
	test_init_list("echo $9", "digit only");

	printf("\n%s===== STUCK / ADJACENT EXPANSIONS =====%s\n", CYAN, RESET);

	/* Adjacent and mixed text */
	test_init_list("echo $USER$HOME", "two vars stuck");
	test_init_list("echo a$USERb", "text-env-text");
	test_init_list("echo $USER\"hola\"", "env then quoted");
	test_init_list("echo \"hola\"$USER", "quoted then env");
	test_init_list("echo \"$USER$HOME\"", "two envs inside quotes");

	printf("\n%s===== UNDEFINED VARIABLES =====%s\n", CYAN, RESET);

	/* Undefined env vars */
	test_init_list("echo $DOES_NOT_EXIST", "undefined var");
	test_init_list("echo a$DOES_NOT_EXISTb", "text + empty + text");
	test_init_list("echo $USER$DOES_NOT_EXIST$HOME", "mixed defined/undefined");

	printf("\n%s===== QUOTES + $ =====%s\n", CYAN, RESET);

	/* Quotes interaction */
	test_init_list("echo \"$\"", "$ inside double quotes");
	test_init_list("echo '$'", "$ inside single quotes");
	test_init_list("echo \"$USER\"", "expand in double quotes");
	test_init_list("echo '$USER'", "no expand in single quotes");

	printf("\n%s===== STRESS TESTS =====%s\n", CYAN, RESET);

	/* Stress & torture tests */
	test_init_list("echo $$$$$$$$", "many empty expansions");
	test_init_list("echo $USER$USER$USER$USER", "repeated env");
	test_init_list("echo a$b$c$d$e", "many small vars");
	test_init_list("echo $", "single dollar only");

	return (0);
}
