/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/16 12:10:20 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	g_status = 42;
	tokenizer_test("./tokenizer/tokenizer_tests.txt");
	printf("\n\n");
	expander_test("./expander/expander_test.txt");
	return (0);
} */

char **get_args(t_token *token)
{
	char **args;
	t_token *ptr = token;

	while (ptr)
		ptr = ptr->next;
	args = malloc(sizeof(char *) * ptr->index + 2);
	ptr = token;
	while (ptr)
	{
		args[ptr->index] = ptr->value;
		ptr = ptr->next;
	}
	args[ptr->index] = NULL;
	return (args);
}

int	main(void)
{
	char *input;
	t_token *token;
	char **arr;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline(PROMPT);
		if (input)
		{
			token = init_list(input);
			arr = get_args(token);
			run_bultins(arr);
		}
		free(input);
	}
	return (0);
}