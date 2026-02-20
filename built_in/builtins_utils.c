/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:40:56 by rick              #+#    #+#             */
/*   Updated: 2026/02/20 14:49:18 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Function returns a pointer to the node matching
* with the value key.*/
t_env	*find_env(t_env **env, char *key)
{
	t_env	*ptr;
	size_t	len;

	ptr = *env;
	len = ft_strlen(key);
	while (ptr)
	{
		if (ft_strncmp(key, ptr->key, len) == 0
			&& ptr->key[len] == '\0')
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
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

/*
* Helper function for b_export that will return a newly 
* allocated string from the begining of the argument until
* finding the "=" or the end of the string argument.*/
char	*get_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}
