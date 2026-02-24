/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:38:46 by rspinell          #+#    #+#             */
/*   Updated: 2026/02/24 22:37:45 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_and_exit(t_data *data, int exit_status)
{
	if (data)
	{
		if (data->token_head)
			free_tokens(&(data->token_head));
		if (data->ast_head)
			free_tree(data->ast_head);
		if (data->env_var)
			free_env_vars(&(data->env_var));
		free_data(data);
	}
	exit(exit_status);
}

/*Frees the data structure*/
void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->env_var)
		free_env_vars(&(data->env_var));
	if (data->pid_values)
		free(data->pid_values);
	free(data);
}

/*
* Frees a null-terminated array of strings up to a specific index.
*/
void	free_splits(char **strs, int index_allocated)
{
	int	index;

	index = 0;
	if (!strs)
		return ;
	while (index < index_allocated)
	{
		free(strs[index]);
		index++;
	}
	free(strs);
}
