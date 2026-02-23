/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:47:48 by rick              #+#    #+#             */
/*   Updated: 2026/02/23 18:24:15 by rspinell         ###   ########.fr       */
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

static void	putsring_echo(char *str, int exit_status, int out_nb)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_strncmp(str + i, "$?", 2))
		{
			ft_putnbr_fd(exit_status, out_nb);
			i = i + 2;
		}
		else
		{
			ft_putchar_fd(str[i], out_nb);
			i++;
		}
	}
}

int	b_echo(char **args, int out_nmb, t_data **data)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	if (!args[1])
	{
		ft_putstr_fd("\n", out_nmb);
		return (0);
	}
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	while (args[i])
	{
		putsring_echo(args[i], (*data)->exit_status, out_nmb);
		if (args[i + 1])
			write(out_nmb, " ", 1);
		i++;
	}
	if (!n_flag)
		write(out_nmb, "\n", 1);
	return (0);
}
