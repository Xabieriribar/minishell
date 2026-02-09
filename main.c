/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/09 17:41:39 by rick             ###   ########.fr       */
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

	// ===== 8. Dollar & Expansion Tests =====
	printf("\n%s===== 8. Dollar & Expansion Tests =====%s\n", CYAN, RESET);
	test_init_list("echo $USER", "WORD(echo), WORD($USER) [D=TRUE]");
	test_init_list("echo '$USER'", "WORD(echo), WORD($USER) [D=FALSE]");
	test_init_list("echo \"Hello $HOME\"", "WORD(echo), WORD(Hello $HOME) [D=TRUE]");
	test_init_list("echo \"\"$HOME\"\"", "WORD(echo), WORD($HOME) [D=TRUE]");
	test_init_list("echo start$USERend", "WORD(echo), WORD(start$USERend) [D=TRUE]");
	test_init_list("echo $VAR1$VAR1", "WORD(echo), WORD(4242) [D=TRUE]");
	test_init_list("echo $UNDEFINED", "WORD(echo), WORD() [D=TRUE]");

	// ===== 9. Heredoc Tests =====
	printf("\n%s===== 9. Heredoc Tests =====%s\n", CYAN, RESET);
	test_init_list("cat << EOF", "WORD(cat), HEREDOC(<<), WORD(EOF) [HDOC=TRUE]");
	test_init_list("cat << 'EOF'", "WORD(cat), HEREDOC(<<), WORD(EOF) [HDOC=FALSE]");
	test_init_list("cat << \"EOF\"", "WORD(cat), HEREDOC(<<), WORD(EOF) [HDOC=FALSE]");
	test_init_list("cat << END_VAR", "WORD(cat), HEREDOC(<<), WORD(END_VAR) [HDOC=TRUE]");

	return (0);
}
