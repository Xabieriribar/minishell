/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:48:02 by rick              #+#    #+#             */
/*   Updated: 2026/02/18 17:34:16 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** =========================================================================
** TODO: b_exit
** =========================================================================
** [ ] Print "exit\n" to STDERR (fd 2).
** [ ] Case 1 (No args): Trigger shell shutdown returning the last command's 
** exit status.
** [ ] Implement `is_valid_exit_number` to parse arg, catch non-digits, 
** signs, and LLONG_MAX/LLONG_MIN overflows.
** [ ] Case 2 (Invalid arg): If `is_valid_exit_number` returns false, print 
** "numeric argument required", set status = 2, and trigger shutdown.
** [ ] Case 3 (Too many args): If arg 1 is valid BUT arg 2 exists, print 
** "too many arguments", set status = 1, and DO NOT shut down (return).
** [ ] Case 4 (Valid arg): Calculate `exit_code % 256`, set it to status, 
** and trigger shutdown.
** [ ] In main loop: Catch the special trigger (e.g., -42), break the loop, 
** free all allocated memory (data, env, tokens), and call exit(status).
*/

//

int b_exit(char **args, t_data *data)
{
	long long	exit_code;

	ft_putstr_fd("exit\n", 2);
	if (!args[1])
		return (-42); 
	if (!valid_number(args[1], &exit_code))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		data->exit_status = 2;
		return (-42);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->exit_status = 1;
		return (1);
	}
	data->exit_status = exit_code % 256;
	return (-42);
}
