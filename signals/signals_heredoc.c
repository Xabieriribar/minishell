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
/* * Used exclusively during heredoc readline loops.
* Closes STDIN to forcefully unblock readline.
*/
void	sigint_heredoc_handler(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	set_heredoc_signals(void)
{
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_stdin(int stdin_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
}
