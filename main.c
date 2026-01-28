/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/01/28 12:57:28 by rspinell         ###   ########.fr       */
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
