/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:47:55 by rick              #+#    #+#             */
/*   Updated: 2026/03/02 11:58:00 by rspinell         ###   ########.fr       */
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
* Function to print the environment variable linked list*/
void	print_env_list(t_env **head, int out_nmb)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->value == NULL)
		{
			tmp = tmp->next;
			continue ;
		}
		ft_putstr_fd(tmp->key, out_nmb);
		ft_putstr_fd("=", out_nmb);
		ft_putstr_fd(tmp->value, out_nmb);
		ft_putstr_fd("\n", out_nmb);
		tmp = tmp->next;
	}
}

/*
* Env without flags will print a list of environment variables.*/
int	b_env(char **arr, t_env **list, int out_nmb)
{
	if (arr[1])
	{
		if (arr[1][0] == '-')
		{
			ft_putstr_fd("env: invalid option -- '", STDERR_FILENO);
			if (arr[1][1])
				ft_putchar_fd(arr[1][1], STDERR_FILENO);
			ft_putendl_fd("'", STDERR_FILENO);
			return (1);
		}
		ft_putstr_fd("env: '", STDERR_FILENO);
		ft_putstr_fd(arr[1], STDERR_FILENO);
		ft_putendl_fd("': No such file or directory", STDERR_FILENO);
		return (1);
	}
	print_env_list(list, out_nmb);
	return (0);
}
