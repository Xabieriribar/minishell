/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:48:13 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 18:25:35 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_pwd(char **args)
{
	char	*str;

	if (args[1] != NULL)
		return(printf("pwd: too many arguments\n"));
	str = getcwd(NULL, 0); 
	if (str == NULL)
		return (perror("getcwd error"), -1);
	printf("%s\n", str);
	free(str); 
	return (0);
}
