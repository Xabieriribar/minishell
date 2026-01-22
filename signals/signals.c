/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:40:04 by rick              #+#    #+#             */
/*   Updated: 2026/01/22 18:22:12 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Signals need to be handle in different cases during the execution 
* of minishell in different ways:

+ 1. During the main loop or "waiting for the user prompt"
+ 2. During execution or "fork()", "execve()" and "waitpid()". */

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();  
	rl_redisplay();
}