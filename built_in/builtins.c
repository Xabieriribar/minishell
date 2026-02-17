/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:40:12 by rick              #+#    #+#             */
/*   Updated: 2026/02/16 17:02:58 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* This function compares the first argument inside the array
* of strings found in the node CMD, and executes the respective
* builtin command.
+ If no command is run returns -1
+ If command found and execution:success returns 0
+ If command found and execution:error, returns 1
+ Errors for each command are handled internally.*/
int	run_bultins(char **args, t_env **list)
{
	if (!args || !*args)
		return (-1);
	if (!ft_strncmp(args[0], "cd", 2))
		return(b_cd(args));
 	if (!ft_strncmp(args[0], "echo", 4))
		return(b_echo(args));
	if (!ft_strncmp(args[0], "env", 3))
		return(b_env(args, list));
/*	if (!ft_strncmp(args[0], "exit", 4));
		return(b_exit(args));
	if (!ft_strncmp(args[0], "export", 6));
		return(b_export(args)); */
	if (!ft_strncmp(args[0], "pwd", 3))
 		return(b_pwd());
/*	if (!ft_strncmp(args[0], "unset", 5));
		return(b_unset(args)); */
	return(0);
}
