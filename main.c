/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/23 16:58:18 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

/*This function mallocs the data struct it and initializes its values to NULL
It returns the struct on success and 1 when somethings goes wrong*/
t_data	*init_data(char **env_variables)
{
	t_data	*data;

	data = malloc(sizeof(struct s_data));
	if (!data)
		return (ft_putstr_fd("Malloc failed\n", STDERR_FILENO), NULL);
	data->env_var = init_env_list(env_variables);
	data->exit_status = 0;
	data->pid_count = 0;
	data->recursive_call_counter = 0;
	data->fd_in = 0;
	data->fd_out = 0;
	data->exit_true = 0;
	data->pid_values = malloc(sizeof(int) * 1024);
	return (data);
}

int	main(int ac, char **av, char **ep)
{
	t_data	*data;
	char	*input;
	t_token	*token;
	t_node	*tree;
	t_token	*temp_token;
	int		exit_code;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)ac;
	(void)av;
	data = init_data(ep);
	if (ac >= 3 && ft_strncmp(av[1], "-c", 3) == 0)
	{
		token = init_list(av[2]);
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
	}
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			rl_clear_history();
			free_all_and_exit(data, data->exit_status);
		}
		if (input && *input)
		{
			add_history(input);
			token = init_list(input);
			if (!token)
			{
				free(input);
				continue ;
			}
			temp_token = token;
			if (grammar_validator(token) != 0)
			{
				data->exit_status = 2;
				free_loop(NULL, &temp_token, input);
				continue ;
			}
			tree = init_tree(&token);
			data->token_head = temp_token;
			execute(data);
			free_loop(data->ast_head, &temp_token, NULL);
			if (data->exit_true == -42)
				break ;
		}
		free(input);
	}
	free_loop(NULL, NULL, input);
	rl_clear_history();
	free_all_and_exit(data, data->exit_status);
}
