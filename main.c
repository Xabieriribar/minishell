/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/19 13:20:36 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

char	**get_args(t_token *token)
{
	char	**args;
	t_token	*ptr;
	int		len;
	int		i;

	ptr = token;
	len = 0;
	while (ptr)
	{
		len++;
		ptr = ptr->next;
	}
	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	ptr = token;
	i = 0;
	while (ptr)
	{
		args[i] = ptr->value;
		ptr = ptr->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	main(int ac, char **av, char **ep)
{
	t_env	*env_list;
	t_data	*data;
	char	*input;
	t_token	*token;
	char	**arr;
	int		ret;

	(void)ac;
	(void)av;
	env_list = init_env_list(ep);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	data = ft_calloc(sizeof(t_data), 1);
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			printf("exit\n");
			free_env_vars(&env_list);
			rl_clear_history();
			exit(0);
		}
		if (input && *input)
		{
			add_history(input);
			token = init_list(input);
			arr = get_args(token);
			ret = run_bultins(arr, &env_list, &data);
			free_tokens(&token);
			if (arr)
				free(arr);
			if (ret == -42)
				break ;
		}
		free(input);
	}
	if (input)
		free(input);
	free_env_vars(&env_list);
	rl_clear_history();
	int asd = data->exit_status;
	free(data);
	return (asd);
}
