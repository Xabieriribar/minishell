/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:40:04 by rick              #+#    #+#             */
/*   Updated: 2026/02/24 23:15:15 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Signals need to be handle in different cases during the execution 
* of minishell in different ways:

+ 1. During the main loop or "waiting for the user prompt"
+ 2. During execution or "fork()", "execve()" and "waitpid()". 

- set_signals_noninteractive()

+  Where: At the very top of execute() (or right before the waitpid loop).

+ Why: The parent shell needs to put on noise-canceling headphones
+ before any commands start running. This stops the double prompt bug.

- set_signals_child()

+ Where: Inside child_process(), right after fork() but before execve().

+ Why: The child inherits the parent's noise-canceling headphones.
+ This function takes them off so commands like cat can
+ actually be killed by Ctrl-C or Ctrl-\.

- set_signals_interactive()

+ Where: At the very end of execute() or wait_for_last_child().
+ Also in main after execution is possible

+ Why: Wakes the parent shell back up so it can listen 
+ for Ctrl-C at the main prompt again.*/
void	sigint_handler(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* 
* Used in main loop */
void	set_signals_interactive(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/* 
* Used by parent right before waiting for children */
void	set_signals_noninteractive(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/* 
* Used by child process right before execve */
void	set_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
