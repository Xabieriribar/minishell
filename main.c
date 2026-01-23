/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/01/23 15:11:58 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
	rl_replace_line("", 0);
    rl_on_new_line();  
    rl_redisplay();
}
*/

int	main(void)
{
<<<<<<< HEAD
	char **tokens= ft_split("ls -la", ' ');
	char **args;
	args = create_args(tokens);
	printf("Hello World");
=======
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
>>>>>>> main
	return (0);
}
