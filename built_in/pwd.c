/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:48:13 by rick              #+#    #+#             */
/*   Updated: 2026/02/18 10:02:09 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (str == NULL)
		return (perror("getcwd error"), 1);
	ft_putstr_fd(str, STDOUT_FILENO);
	write(1, "\n", 1);
	free(str);
	return (0);
}
