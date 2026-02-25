/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/20 15:01:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Iterates through the environment linked list to find the PATH variable.
*/
t_env	*return_path(t_env *env_var)
{
	while (env_var)
	{
		if (env_var->key && !ft_strncmp(env_var->key, "PATH", 5))
			return (env_var);
		env_var = env_var->next;
	}
	return (NULL);
}

/*
* Helper to concatenate key, '=' and value into a single string for execve.
*/
static char	*join_env_entry(t_env *node)
{
	char	*temp;
	char	*full_entry;

	temp = ft_strjoin(node->key, "=");
	if (!temp)
		return (NULL);
	full_entry = ft_strjoin(temp, node->value);
	free(temp);
	return (full_entry);
}

/*
* Converts the internal environment linked list into a char** array.
*/
char	**convert_env_var_to_array(t_env *env_var, int lstsize)
{
	char	**result;
	int		i;

	if (!env_var)
		return (NULL);
	result = malloc(sizeof(char *) * (lstsize + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (env_var)
	{
		result[i] = join_env_entry(env_var);
		if (!result[i])
		{
			free_splits(result, i);
			return (NULL);
		}
		env_var = env_var->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

/*
* Returns the number of elements in the environment linked list.
*/
int	ft_env_var_lstsize(t_env *env_var)
{
	int	lstsize;

	lstsize = 0;
	while (env_var)
	{
		lstsize++;
		env_var = env_var->next;
	}
	return (lstsize);
}
