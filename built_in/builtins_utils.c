/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:40:56 by rick              #+#    #+#             */
/*   Updated: 2026/02/19 16:48:34 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Function to free the environment variable linked list*/
void	free_env_vars(t_env **head)
{
	t_env	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->key);
		free((*head)->value);
		free(*head);
		*head = tmp;
	}
}

/*
* Helper function to get size of array of t_env.
* Used in b_export.*/
int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/*
* Helper function to sort the array of t_env.
* Used in b_export.*/
void	sort_env_arr(t_env **arr, int size)
{
	t_env	*temp;
	int		j;
	int		i;
	size_t	len;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			len = ft_strlen(arr[j]->key) + 1;
			if (ft_strncmp(arr[j]->key, arr[j + 1]->key, len) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/*
* Helper function to print the array of t_env.
* Used in b_export.*/
void	print_arr(t_env **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(arr[i]->key, 1);
		if (arr[i]->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(arr[i]->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}
