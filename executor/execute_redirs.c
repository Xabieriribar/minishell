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
* Handles input redirections (<) and heredocs (<<).
* Closes the previous file descriptor if it was already modified.
* If a file cannot be opened, it either returns an error (parent) 
* or exits cleanly (child).
*/
static int	handle_in_redir(t_redirs *redir, int *fd_in, t_data *data)
{
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	*fd_in = open(redir->filename, O_RDONLY);
	if (*fd_in < 0)
	{
		if (data->flag)
			return (-1);
		write_error_message(redir->filename);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_all_and_exit(data, EXIT_FAILURE);
	}
	return (0);
}

/*
* Handles output redirections (>) and append redirections (>>).
* Uses O_TRUNC for (>) and O_APPEND for (>>).
*/
static int	handle_out_redir(t_redirs *redir, int *fd_out, t_data *data)
{
	int	flags;

	if (*fd_out != STDOUT_FILENO)
		close(*fd_out);
	flags = O_WRONLY | O_CREAT;
	if (redir->redir_type == T_REDIR_OUT)
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;
	*fd_out = open(redir->filename, flags, 0644);
	if (*fd_out < 0)
	{
		if (data->flag)
			return (-1);
		write_error_message(redir->filename);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_all_and_exit(data, EXIT_FAILURE);
	}
	return (0);
}

/*
* Iterates through the redirection list and updates the current command's
* input and output file descriptors. 
* data->flag identifies if we are in the parent (builtin) or child.
*/
int	update_fd(t_redirs *redirs, int *fd_in, int *fd_out, t_data *data)
{
	t_redirs	*temp;
	int			status;

	temp = redirs;
	while (temp)
	{
		status = 0;
		if (temp->redir_type == T_REDIR_IN || temp->redir_type == T_HEREDOC)
			status = handle_in_redir(temp, fd_in, data);
		else if (temp->redir_type == T_REDIR_OUT
			|| temp->redir_type == T_REDIR_APPEND)
			status = handle_out_redir(temp, fd_out, data);
		if (status == -1)
			return (-1);
		temp = temp->next;
	}
	return (0);
}
