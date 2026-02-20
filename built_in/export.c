/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:48:07 by rick              #+#    #+#             */
/*   Updated: 2026/02/20 15:12:09 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Checks if a string is a valid Bash identifier.*/
static bool	valid_key(char *str)
{
	int	i;

	if (!str || !str[0] || str[0] == '=')
		return (false);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/*
* Function to sort and print the environment variables
* list.
+ Used for case where export has no arguments.*/
static void	sort_and_print_export(t_env *env, int out_nmb)
{
	t_env	**arr;
	t_env	*temp;
	int		size;
	int		i;

	size = env_list_size(env);
	arr = malloc(sizeof(t_env *) * size);
	if (!arr)
		return ;
	i = 0;
	temp = env;
	while (temp)
	{
		arr[i++] = temp;
		temp = temp->next;
	}
	sort_env_arr(arr, size);
	print_arr(arr, size, out_nmb);
	free(arr);
}

static int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (1);
}

/*
* Function to add or update an environment variable.
* This will check if the variable exists or not, and either
* update the value or create a new node in the env list.*/
static int	update_or_add(t_env **env, char *arg, char *key)
{
	t_env	*ptr;
	char	*eq;

	ptr = find_env(env, key);
	eq = ft_strchr(arg, '=');
	if (ptr && eq)
	{
		free(ptr->value);
		ptr->value = ft_strdup(eq + 1);
		if (!ptr->value)
			return (1);
	}
	else if (!ptr)
	{
		if (lst_add_back_env(env, init_env(arg)))
			return (1);
	}
	return (0);
}

/*
* Main export function.
* If there is no arguments for export:
	- Print in alphabetical order the list of env
* If arguments:
	- Check the valitity of the arguments
	- Modify or add a env according to the arguments.*/
int	b_export(char **arr, t_env **env, int out_nmb)
{
	int		i;
	int		status;
	char	*key;

	i = 0;
	status = 0;
	if (!arr[1])
		return (sort_and_print_export(*env, out_nmb), 0);
	while (arr[++i])
	{
		if (!valid_key(arr[i]))
			status = export_error(arr[i]);
		else
		{
			key = get_key(arr[i]);
			if (update_or_add(env, arr[i], key))
			{
				free(key);
				return (1);
			}
			free(key);
		}
	}
	return (status);
}
