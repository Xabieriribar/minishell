/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/20 15:01:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Checks if the redirection list contains any output redirections 
* (either truncate or append). Returns 1 if found, 0 otherwise.
*/
int	contains_out_redirs(t_redirs *redirs)
{
	t_redirs	*temp;

	temp = redirs;
	while (temp)
	{
		if (temp->redir_type == T_REDIR_OUT
			|| temp->redir_type == T_REDIR_APPEND)
			return (1);
		temp = temp->next;
	}
	return (0);
}

/*
* Checks if the redirection list contains any input redirections 
* (either standard input or heredoc). Returns 1 if found, 0 otherwise.
*/
int	contains_in_redirs(t_redirs *redirs)
{
	t_redirs	*temp;

	temp = redirs;
	while (temp)
	{
		if (temp->redir_type == T_REDIR_IN || temp->redir_type == T_HEREDOC)
			return (1);
		temp = temp->next;
	}
	return (0);
}

/*
* Iterates through a string to check for the presence of a forward slash.
* This is used to determine if a command is a relative/absolute path.
*/
int	contains_slash(char *suspect)
{
	int	i;

	i = 0;
	if (!suspect)
		return (0);
	while (suspect[i])
	{
		if (suspect[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

/*
* Safely closes file descriptors if they are not the standard 
* input (0) or standard output (1).
*/
void	close_if_not_stdin_or_stdout(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO && fd_in != -1)
		close(fd_in);
	if (fd_out != STDOUT_FILENO && fd_out != -1)
		close(fd_out);
}

/*
* Checks if a specific file/path exists and has execution permissions.
* If accessible, returns a duplicate of the command string; otherwise NULL.
*/
char	*can_access(char *command)
{
	if (access(command, F_OK | X_OK) == -1)
		return (NULL);
	return (ft_strdup(command));
}
