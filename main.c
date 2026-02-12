/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 11:03:14 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_status = 0;

int	main(void)
{
	g_status = 42;
	tokenizer_test("./tokenizer/tokenizer_tests.txt");
	printf("\n\n");
	expander_test("./expander/expander_test.txt");
	return (0);
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