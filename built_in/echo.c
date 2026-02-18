/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:47:48 by rick              #+#    #+#             */
/*   Updated: 2026/02/18 10:02:32 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (false);
	if (!str[1])
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	b_echo(char **args)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
