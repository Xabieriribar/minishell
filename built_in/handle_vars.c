/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:10:23 by rick              #+#    #+#             */
/*   Updated: 2026/03/04 12:33:47 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* This function will check the syntax of the argument passed to
* check if it should or not create a temp env variable.
* On failure, will continue program normal executon
* On success, will add to the list on env variables a new variable
* or modify one in case of having to be modified. */
int	make_temp_var(t_data *data, char **arr)
{
	char	*key;

	if (!arr || !arr[0] || arr[1] != NULL || !ft_strchr(arr[0], '='))
		return (0);
	if (!valid_key(arr[0]))
		return (0);
	key = get_key(arr[0]);
	if (update_or_add(&(data->env_var), arr[0], key, TEMP_VAR))
	{
		free(key);
		return (1);
	}
	free(key);
	data->exit_status = 0;
	return (1);
}

/* 
* Helper function for update_or_add() */
static int	update_existing_var(t_env *ptr, char *eq, int type)
{
	if (eq)
	{
		free(ptr->value);
		ptr->value = ft_strdup(eq + 1);
		if (!ptr->value)
		{
			perror("Err: Malloc");
			return (1);
		}
	}
	if (type == EXP_VAR)
		ptr->temp = false;
	return (0);
}

/*
* Function to add or update an environment variable.
* This will check if the variable exists or not, and either
* update the value or create a new node in the env list.*/
int	update_or_add(t_env **env, char *arg, char *key, int type)
{
	t_env	*ptr;
	char	*eq;

	ptr = find_env(env, key);
	eq = ft_strchr(arg, '=');
	if (ptr)
		return (update_existing_var(ptr, eq, type));
	ptr = init_env(arg);
	if (!ptr)
		return (1);
	lst_add_back_env(env, ptr);
	if (type == TEMP_VAR)
		ptr->temp = true;
	return (0);
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
