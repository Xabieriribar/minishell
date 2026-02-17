/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:40:56 by rick              #+#    #+#             */
/*   Updated: 2026/02/17 14:15:21 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
* Returns a pointer to the last element of the list of
* environment variables.*/
static t_env	*lstlast_env(t_env *lst)
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
* Adds a env variable node to the last position of the list*/
static int	lst_add_back_env(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (!new)
		return (1);
	new->next = NULL;
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
* Inits a single environment variable node.*/
static t_env	*init_env(char *str)
{
	t_env	*env;
	char	*eq_ptr;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (perror("Malloc"), NULL);
	eq_ptr = ft_strchr(str, '=');
	if (eq_ptr)
		env->key = ft_substr(str, 0, eq_ptr - str);
	else
		env->key = ft_strdup(str);
	if (!env->key)
		return (perror("Malloc"), free(env), NULL);
	if (eq_ptr)
	{
		env->value = ft_strdup(eq_ptr + 1);
		if (!env->value)
			return (perror("Malloc"), free(env->key), free(env), NULL);
	}
	else
		env->value = NULL;
	env->next = NULL;
	return (env);
}

/*
* Inits the environment variable linked list.*/
t_env	*init_env_list(char **envp)
{
	int		i;
	t_env	*head;
	int		err_check;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		err_check = lst_add_back_env(&head, init_env(envp[i]));
		if (err_check)
			return (free_env_vars(&head), NULL);
		i++;
	}
	return (head);
}

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

/* char **env_to_array(t_env *env)
{
    t_env   *tmp;
    char    **arr;
    int     len;
    int     i;

    // 1. Count nodes
    len = 0;
    tmp = env;
    while (tmp)
    {
        len++;
        tmp = tmp->next;
    }

    // 2. Allocate array (len + 1 for NULL terminator)
    arr = malloc(sizeof(char *) * (len + 1));
    if (!arr)
        return (NULL);

    // 3. Fill array´
    i = 0;
    tmp = env;
    while (tmp)
    {
        // Join KEY + "=" + VALUE
        arr[i] = join_key_value(tmp->key, tmp->value); 
        if (!arr[i])
        {
            free_matrix(arr); // Helper to free everything on error
            return (NULL);
        }
        tmp = tmp->next;
        i++;
    }
    arr[i] = NULL; // Null-terminate the array
    return (arr);
}
 */