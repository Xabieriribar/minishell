/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:47:55 by rick              #+#    #+#             */
/*   Updated: 2026/02/17 11:18:14 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Function to print the environment variable linked list*/
void	print_env_list(t_env **head)
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
		ft_putstr_fd(tmp->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(tmp->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
}

int b_env(char **arr, t_env **list)
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
    print_env_list(list);
    return (0);
}
