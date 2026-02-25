/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:32:45 by lalex-ku          #+#    #+#             */
/*   Updated: 2026/02/24 20:26:13 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char const *argv[])
{
	int	pid;

	pid = fork();
	open("infile", O_RDONLY);
	while (1)
	{
		printf("Helloo miniHELL %i\n", pid);
		sleep(1);
	}
	return (0);
}

	if (ac >= 3 && ft_strncmp(av[1], "-c", 3) == 0)
	{
		token = init_list(av[2], data);
		if (!token)
		{
			free_data(data);
			exit(0);
		}
		temp_token = token;
		if (grammar_validator(token) != 0)
		{
			data->exit_status = 2;
			free_tokens(&temp_token);
		}
		else
		{
			tree = init_tree(&token);
			free(token);
			execute(tree, data);
			free_tokens(&temp_token);
			free_tree(tree);
		}
		exit_code = data->exit_status;
		free_data(data);
		exit(exit_code);
	} */
	/* --------------------------------------- */