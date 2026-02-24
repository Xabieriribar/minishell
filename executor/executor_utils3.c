/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:35:40 by rspinell          #+#    #+#             */
/*   Updated: 2026/02/23 18:23:58 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error_message(char *cmd)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
}

void	command_not_found_error(char *cmd, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_all_and_exit(data, 127);
}

void	no_such_file_or_directory_error(char *cmd, t_data *data, int flag)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (flag)
		free_all_and_exit(data, 1);
	else
		free_all_and_exit(data, 127);
}

void	is_a_directory_error(char *cmd, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Is a directory", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_all_and_exit(data, 126);
}

void	permission_denied_error(char *cmd, t_data *data, int flag)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Permission denied", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (flag)
		free_all_and_exit(data, 1);
	else
		free_all_and_exit(data, 126);
}

void	unlink_heredoc_files(t_node *tree)
{
	if (!tree->left_child)
	{
		unlink(tree->redirs->filename);
		return;
	}
	unlink(tree->right_child->redirs->filename);
	unlink_heredoc_files(tree->left_child);
}
