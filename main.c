/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/01/18 12:03:28 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char **tokens= ft_split("ls -la", ' ');
	char **args;
	args = create_args(tokens);
	printf("Hello World");
	return (0);
}