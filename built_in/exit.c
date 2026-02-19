/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:48:02 by rick              #+#    #+#             */
/*   Updated: 2026/02/19 15:41:48 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_spaces(char *str, int *ix)
{
	while (is_space(str[*ix]))
		*ix = *ix + 1;
}

static bool	off_limits(long long exit_code, char c, int sign)
{
	if (exit_code > LLONG_MAX / 10)
		return (true);
	if (exit_code == LLONG_MAX / 10
		&& (c - '0') > (LLONG_MAX % 10) + (sign == -1))
		return (true);
	return (false);
}

static bool	valid_number(char *arr, long long *exit_code)
{
	int	sign;
	int	ix;

	ix = 0;
	sign = 1;
	skip_spaces(arr, &ix);
	if ((arr[ix] == '+') || (arr[ix] == '-'))
	{
		if (arr[ix] == '-')
			sign *= -1;
		ix++;
	}
	while ((arr[ix] >= '0') && (arr[ix] <= '9'))
	{
		if (off_limits(*exit_code, arr[ix], sign))
			return (false);
		*exit_code = *exit_code * 10 + arr[ix] - '0';
		ix++;
	}
	*exit_code = *exit_code * sign;
	skip_spaces(arr, &ix);
	if (arr[ix] != '\0')
		return (false);
	return (true);
}

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
