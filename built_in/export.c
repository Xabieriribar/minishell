/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:48:07 by rick              #+#    #+#             */
/*   Updated: 2026/03/04 12:26:21 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Checks if a string is a valid Bash identifier.*/
bool	valid_key(char *str)
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
	t_env	*node;
	int		size;
	int		i;

	size = env_list_size(env);
	arr = ft_calloc(sizeof(t_env *), size);
	if (!arr)
		return ;
	i = 0;
	node = env;
	while (node)
	{
		if (node->temp == false)
		{
			arr[i++] = node;
		}
		node = node->next;
	}
	sort_env_arr(arr, i);
	print_arr(arr, i, out_nmb);
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
	/*
	if (!(*env)) 
	~ SI EP LLEGA VACIO DE LA EJECUCION, USAMOS GETENV? COMO ESESO?
		*env = init_env_list(data->ep)
	*/
	if (!arr[1])
		return (sort_and_print_export(*env, out_nmb), 0);
	while (arr[++i])
	{
		if (!valid_key(arr[i]))
			status = export_error(arr[i]);
		else
		{
			key = get_key(arr[i]);
			if (update_or_add(env, arr[i], key, EXP_VAR))
			{
				free(key);
				return (1);
			}
			free(key);
		}
	}
	return (status);
}
