/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/24 22:41:51 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_status = 0;

/*This function mallocs the data struct it and initializes its values to NULL
It returns the struct on success and 1 when somethings goes wrong*/
t_data	*init_data(char **env_variables)
{
	t_data	*data;

	data = malloc(sizeof(struct s_data));
	if (!data)
		return (perror("Malloc failed when initializing the data struct"), NULL);
	data->env_var = init_env_list(env_variables);
	data->exit_status = 0;
	data->pid_count  = 0;
	data->recursive_call_counter = 0;
	data->fd_in = 0;
	data->fd_out = 0;
	data->pid_values = malloc(sizeof(int) * 1024);
	return (data);
}

/* static void	process_input(t_data *data)
{
	t_token	*token;
	t_token	*head;
	t_node	*tree;

	add_history(data->input);
	token = init_list(data->input, data);
	if (!token)
		return ;
	head = token;
	if (grammar_validator(token) != 0)
	{
		data->exit_status = 2;
		free_tokens(&head);
		return ;
	}
	tree = init_tree(&token);
	data->ast_head = tree;
	data->token_head = head;
	execute(tree, data);
	free_tokens(&head);
	data->token_head = NULL; // Prevent double free on exit!
	free_tree(tree);
	data->ast_head = NULL;
}

static void	shell_loop(t_data *data)
{
	while (1)
	{
		data->input = readline(PROMPT);
		if (!data->input)
			break ;
		if (data->input[0])
		{
			process_input(data);
			if (data->exit_true == -42)
				break ;
		}
		free(data->input);
	}
}

int	main(int ac, char **av, char **ep)
{
	t_data	*data;
	int		exit_code;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	data = init_data(ep);
	shell_loop(data);
	if (data->input)
		free(data->input);
	exit_code = data->exit_status;
	rl_clear_history();
	free_all_and_exit(data, exit_code);
	return (exit_code);
} */

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
	}
	/* --------------------------------------- */
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			free_env_vars(&(data->env_var));
			rl_clear_history();
			exit(0);
		}
		if (input && *input)
		{
			add_history(input);
			token = init_list(input, data);
			if (!token)
			{
				free(input);
				continue ;
			}
			temp_token = token;
			if (grammar_validator(token) != 0)
			{
				data->exit_status = 2;
				free_tokens(&temp_token);
				free(input);
				continue ;
			}
			tree = init_tree(&token);
			data->ast_head = tree;
			data->token_head = temp_token;
			execute(tree, data);
			free_tokens(&temp_token);
			free_tree(tree);
			if (data->exit_true == -42)
				break ;
		}
		free(input);
	}
	if (input)
		free(input);
	rl_clear_history();
	exit_code = data->exit_status;
	free_data(data);
	return (exit_code);
}
