/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:40:56 by rick              #+#    #+#             */
/*   Updated: 2026/03/04 12:34:04 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
* Adds a env variable node to the last position of the list*/
int	lst_add_back_env(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (!new)
		return (1);
	new->next = NULL;
	new->temp = false;
	ptr = lstlast_env(*lst);
	if (!ptr)
	{
		*lst = new;
		return (0);
	}
	ptr->next = new;
	return (0);
}

/* 
* Returns a pointer to the last element of the list of
* environment variables.*/
t_env	*lstlast_env(t_env *lst)
{
	t_env	*ptr;

	ptr = lst;
	if (!lst)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
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
void	print_arr(t_env **arr, int size, int out_nmb)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_putstr_fd("declare -x ", out_nmb);
		ft_putstr_fd(arr[i]->key, out_nmb);
		if (arr[i]->value)
		{
			ft_putstr_fd("=\"", out_nmb);
			ft_putstr_fd(arr[i]->value, out_nmb);
			ft_putstr_fd("\"", out_nmb);
		}
		ft_putstr_fd("\n", out_nmb);
		i++;
	}
}
