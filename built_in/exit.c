/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:48:02 by rick              #+#    #+#             */
/*   Updated: 2026/02/20 15:04:49 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Helper to advance in a string while is_space is true.*/
static void	skip_spaces(char *str, int *ix)
{
	while (is_space(str[*ix]))
		*ix = *ix + 1;
}

/*
* Helper to handle the overflow long long case for exit status nbr.*/
static bool	off_limits(long long exit_code, char c, int sign)
{
	if (exit_code > LLONG_MAX / 10)
		return (true);
	if (exit_code == LLONG_MAX / 10
		&& (c - '0') > (LLONG_MAX % 10) + (sign == -1))
		return (true);
	return (false);
}

/*
* The "atoi" of exit, works with a long long handling the respective
* overflow, and modifing the exit_code value according to the
* recieved exit [argument]*/
static bool	valid_number(char *arg, long long *exit_code)
{
	int	sign;
	int	ix;

	ix = 0;
	sign = 1;
	skip_spaces(arg, &ix);
	if ((arg[ix] == '+') || (arg[ix] == '-'))
	{
		if (arg[ix] == '-')
			sign *= -1;
		ix++;
	}
	while ((arg[ix] >= '0') && (arg[ix] <= '9'))
	{
		if (off_limits(*exit_code, arg[ix], sign))
			return (false);
		*exit_code = *exit_code * 10 + arg[ix] - '0';
		ix++;
	}
	*exit_code = *exit_code * sign;
	skip_spaces(arg, &ix);
	if (arg[ix] != '\0')
		return (false);
	return (true);
}

/*
* Exit function will print the exit message in STDERR
* Then will modify the data->exit_status according to the
* arguments or not and will return -42, value un specific used
* To stop the main loop of the function, to then free
* all the allocated memory and exit the program.*/
int	b_exit(char **arr, t_data **data)
{
	long long	exit_code;

	exit_code = 0;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!arr[1])
		return (-42);
	if (!valid_number(arr[1], &exit_code))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(arr[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		(*data)->exit_status = 2;
		return (-42);
	}
	if (arr[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		(*data)->exit_status = 1;
		return (1);
	}
	(*data)->exit_status = exit_code % 256;
	return (-42);
}
