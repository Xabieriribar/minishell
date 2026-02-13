/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 19:28:36 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// int main(void)
// {
// 	int fd_grammar_tester = open("parser/grammar_tests/grammar_tester.txt", O_RDONLY);
// 	if (fd_grammar_tester < 0)
// 		perror("Failed to open tester file");
// 	if (test_grammar(fd_grammar_tester) != 0)
// 		return (perror("Failed to test grammar"), 1);
// 	return 0;
// }
volatile sig_atomic_t g_status = 0;
int main(void)
{

	int fd_tree_tester = open("parser/tree_tester/tree_tests.txt", O_RDONLY);
	if (fd_tree_tester < 0)
		perror("Failed to open tester file");
	if (test_tree(fd_tree_tester) != 0)
		return (perror("Failed to test tree"), 1);
	close(fd_tree_tester);
	return 0;
}

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