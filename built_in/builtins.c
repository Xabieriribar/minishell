/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:40:12 by rick              #+#    #+#             */
/*   Updated: 2026/02/20 15:21:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* This function compares the first argument inside the array
* of strings found in the node CMD, and executes the respective
* builtin command if found.

- This function updates the exit_status in t_data.

+ If no bultin is run: return (-1)
		- This is the case where we call execve()
+ If builtin found && execution:success
		- returns (0)
+ If builtin found and execution:error
		- returns (1 or 2)

~ SPECIAL CASE FOR b_exit()

+ If builtin is b_exit()
	- return value is -42 on success
+ This special case is intended for main to catch this
+ return value and break the main loop, to then free everything
+ and terminate the program.
+ b_exit() setst the exit_status to handle users input in that sense. */
int	run_bultins(char **args, t_env **list, t_data **data, int out_nmb)
{
	int	ret;

	if (!args || !*args)
		return (-1);
	if (!ft_strncmp(args[0], "exit", 5))
		return (b_exit(args, data));
	if (!ft_strncmp(args[0], "cd", 3))
		ret = b_cd(*list, args, out_nmb);
	else if (!ft_strncmp(args[0], "echo", 5))
		ret = b_echo(args, out_nmb, data);
	else if (!ft_strncmp(args[0], "env", 4))
		ret = b_env(args, list, out_nmb);
	else if (!ft_strncmp(args[0], "pwd", 4))
		ret = b_pwd(out_nmb);
	else if (!ft_strncmp(args[0], "unset", 6))
		ret = b_unset(list, args);
	else if (!ft_strncmp(args[0], "export", 7))
		ret = b_export(args, list, out_nmb);
	else
		return (-1);
	(*data)->exit_status = ret;
	return (ret);
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
* Adds a env variable node to the last position of the list*/
int	lst_add_back_env(t_env **lst, t_env *new)
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
t_env	*init_env(char *str)
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
