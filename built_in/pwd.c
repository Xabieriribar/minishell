/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:48:13 by rick              #+#    #+#             */
/*   Updated: 2026/02/19 18:37:19 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_pwd(int out_nbr)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (str == NULL)
		return (perror("getcwd error"), STDERR_FILENO);
	ft_putstr_fd(str, out_nbr);
	write(1, "\n", 1);
	free(str);
	return (0);
}
