/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/26 17:53:57 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Handles input redirections (<) and heredocs (<<).
* Closes the previous file descriptor if it was already modified.
* If a file cannot be opened, it either returns an error (parent) 
* or exits cleanly (child).
*/
static int	check_for_ambiguous_error(t_redirs *redir, t_data *data)
{
	if (!ft_strncmp(redir->filename, "", 2))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->filename, 2);
		ft_putstr_fd("ambiguous redirect\n", 2);
		free_all_and_exit(data, 1);
	}
	else if ()
	return (0);
}
static int	handle_in_redir(t_redirs *redir, int *fd_in, t_data *data)
{
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	*fd_in = open(redir->filename, O_RDONLY, 0644);
	if (*fd_in < 0)
	{
		if (data->flag)
			return (-1);
		if (!check_for_ambiguous_erorr(redir, data))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redir->filename, 2);
			ft_putstr_fd("ambiguous redirect\n", 2);
			free_all_and_exit(data, 1);
		}
		check_possible_errors(redir->filename, data, 1);
	}
	return (0);
}

/*
* Handles output redirections (>) and append redirections (>>).
* Uses O_TRUNC for (>) and O_APPEND for (>>).
*/
static int	handle_out_redir(t_redirs *redir, int *fd_out, t_data *data)
{
	if (*fd_out != STDOUT_FILENO)
		close(*fd_out);
	if (redir->redir_type == T_REDIR_OUT)
		*fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->redir_type == T_REDIR_APPEND)
		*fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd_out < 0)
	{
		if (data->flag)
			return (-1);
		check_possible_errors(redir->filename, data, 1);
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
