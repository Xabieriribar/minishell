/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:48:18 by rick              #+#    #+#             */
/*   Updated: 2026/02/18 11:31:47 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Function returns a pointer to the previous node that needs
* to be deletede from the list.*/
static t_env	*get_delete(t_env **env, char *key)
{
	t_env	*ptr;
	size_t	len;

	ptr = *env;
	len = ft_strlen(key);
	while (ptr)
	{
		if (!ptr->next)
			break ;
		if (ft_strncmp(key, ptr->next->key, len) == 0
			&& ptr->next->key[len] == '\0')
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

/*
* Simple helper free function*/
static void	free_env(t_env *env)
{
	if (!env)
		return ;
	env->next = NULL;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

/*
* Deletes the node matching with the key value from the list.*/
static void	delete_env(t_env **env, char *key)
{
	t_env	*ptr;
	t_env	*to_delete;
	size_t	len;

	len = ft_strlen(key);
	ptr = *env;
	if (ptr && ft_strncmp(key, ptr->key, len) == 0
		&& ptr->key[len] == '\0')
	{
		*env = (*env)->next;
		free_env(ptr);
	}
	else
	{
		ptr = get_delete(env, key);
		if (!ptr)
			return ;
		to_delete = ptr->next;
		ptr->next = to_delete->next;
		free_env(to_delete);
	}
}

/*
* Deletes environment variables. Returns 0 on success or 
* 1 if at least one of the vars had a wrong format.
* In case of not finding the variable will still return 0*/
int	b_unset(t_env **env, char **arr)
{
	int	i;

	if (!arr[1])
		return (0);
	i = 1;
	while (arr[i])
	{
		delete_env(env, arr[i]);
		i++;
	}
	return (0);
}
