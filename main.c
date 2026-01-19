/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/01/18 17:46:23 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	//test_init_list("< infile grep 'adios mundo' | cat hostname >> outfile");
	char **arr;
	
	arr = ft_split("hola como estas", ' ');
	arr[2][1] = 'p';
	return (0);
}
