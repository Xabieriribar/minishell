/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 19:22:03 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int main(void)

volatile sig_atomic_t g_status = 0;

/* int main(void)
{
	char *str[] = {"cd", "../Common-Core", NULL};
 	char *str2[] = {"pwd", NULL};
	b_pwd(str2);
	b_cd(str);
	return (0);
} */

/* int	main(void)
{
	int fd_grammar_tester = open("parser/grammar_tests/grammar_tester.txt", O_RDONLY);
	if (fd_grammar_tester < 0)
		perror("Failed to open tester file");
	if (test_grammar(fd_grammar_tester) != 0)
		return (perror("Failed to test grammar"), 1);
	return 0;
}
	g_status = 42;
	tokenizer_test("./tokenizer/tokenizer_tests.txt");
	printf("\n\n");
	expander_test("./expander/expander_test.txt");
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